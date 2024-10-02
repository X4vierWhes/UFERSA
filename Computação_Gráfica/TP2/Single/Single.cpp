/**********************************************************************************
// Single (Código Fonte)
//
// Criação:     27 Abr 2016
// Atualização: 15 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Constrói cena com um único buffer de vértices e índices
//
**********************************************************************************/

#include "DXUT.h"

// ------------------------------------------------------------------------------

struct ObjectConstants
{
    XMFLOAT4X4 WorldViewProj =
    { 1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f };
};

struct Location {
    int baseVertex; //Localização inicial do objeto no vetor de vertices
    int vertexCount; //Localização final delimitada pelo tamanho de vertices da figura
};

// ------------------------------------------------------------------------------

class Single : public App
{
private:
    ID3D12RootSignature* rootSignature = nullptr;
    ID3D12PipelineState* pipelineState = nullptr;
    vector<Object> scene; //Coloca todos os objetos
    Mesh* mesh = nullptr;

    Timer timer;
    bool spinning = true;

    XMFLOAT4X4 Identity = {};
    XMFLOAT4X4 View = {};
    XMFLOAT4X4 Proj = {};

    float theta = 0;
    float phi = 0;
    float radius = 0;
    float lastMousePosX = 0;
    float lastMousePosY = 0;

    uint objectsInScene = 1; //Quantidade de Objetos em cena
    uint totalIndexCount = 0; //Quantidade de index
    uint totalVertexCount = 0; //Quantidade de vertices
    Location* objLocation = nullptr; //Struct que criei para marcar inicio e fim
    Vertex* vertices = nullptr; //Ponteiro para vetor de vertices
    vector<uint> indices; //Vector de indices
    uint objAmount = 10; //Inicia com 10 objetos possiveis;
    int tab = -1; //Controle do TAB

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
    void AddObjectToScene(Geometry& newObject, float scaleX, float scaleY, float scaleZ);
    void DeleteObjectToScene();
    void SelectObjectInScene();

    void BuildRootSignature();
    void BuildPipelineState();
};

// ------------------------------------------------------------------------------
// Funções para ajuda e Legibilidade do codigo

//Função "Template" para adicionar qualquer objeto na cena
void Single::AddObjectToScene(Geometry& newObject, float scaleX, float scaleY, float scaleZ) { 
    graphics->ResetCommands();
    //Calcula novos tamanhos
    uint newTotalVertexCount = totalVertexCount + newObject.VertexCount();
    const uint vbSize = newTotalVertexCount * sizeof(Vertex);

    uint newTotalIndexCount = totalIndexCount + newObject.IndexCount();
    const uint ibSize = newTotalIndexCount * sizeof(uint);
    //Cria vetor auxiliar
    Vertex* aux = new Vertex[newTotalVertexCount];
    int k = 0;
    //Copiando vetor de vertices
    for (uint i{}; i < totalVertexCount; i++, k++) {
        aux[k].pos = vertices[i].pos;
        aux[k].color = vertices[i].color;
    }
    //Adicionando novo objeto no vetor auxiliar que virara o novo vetor de vertices
    for (uint i{}; i < newObject.VertexCount(); i++, k++) {
        aux[k].pos = newObject.vertices[i].pos;
        aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
    }
    //Localição dos vertices (Inicio e Fim) no vetor de vertices
    objLocation[objectsInScene] = Location{ (int)totalVertexCount, (int)newObject.VertexCount()};
    //Indices para desenhar os objetos estão colocados em sequencia
    indices.insert(indices.end(), begin(newObject.indices), end(newObject.indices));
    //Criando SubMesh do novo objeto
    SubMesh newSubMesh;
    newSubMesh.indexCount = uint(newObject.IndexCount()); //Numero de indices necessarios para desenhar o objeto
    newSubMesh.startIndex = totalIndexCount; //Onde inicia no vetor de vertices
    newSubMesh.baseVertex = totalVertexCount; //Indice de vertice que ele considera o "0" no vetor de vertices

    Object obj; //Criando Objeto pra colocar na cena
    XMStoreFloat4x4(&obj.world,
        XMMatrixScaling(scaleX, scaleY, scaleZ) *
        XMMatrixTranslation(0.0f, 0.0f, 0.0f)); //Movimentando ele no mundo
    obj.cbIndex = objectsInScene; //Index no Buffer
    obj.submesh = newSubMesh; //SubMesh do objeto
    scene.push_back(obj); //Adicionando no vetor de cenas

    objectsInScene++; //Aumentando quantidade de objetos na cena

    delete[] vertices; //Deletando vetor antigo

    totalVertexCount = newTotalVertexCount; //Atualizando total de vertices
    totalIndexCount = newTotalIndexCount; //Atualizando totla de indices

    vertices = aux; //Novo vetor de vertices

    mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
    mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
    mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

    graphics->SubmitCommands();
}

void Single::DeleteObjectToScene() {

    if (tab != -1 && objectsInScene > 0) {
        graphics->ResetCommands();
        //Calculando novos totais
        int newTotalVertex = totalVertexCount - objLocation[tab].vertexCount;
        int newTotalIndex = totalIndexCount - scene.at(tab).submesh.indexCount;

        int vertexToRemove = objLocation[tab].vertexCount;
        int indexToRemove = scene.at(tab).submesh.indexCount;
        //Criando novo vetor
        Vertex* aux = new Vertex[newTotalVertex];
        int k = 0;
        for (int i{}; i < objLocation[tab].baseVertex; i++,k++) { //Copiando inicio do vetor ate chegar no começo do vetor que desejamos deletar
            aux[k] = vertices[i];
        }

        for (int i{ objLocation[tab].baseVertex + objLocation[tab].vertexCount }; i < totalVertexCount; i++, k++) { //Copiando o que vem depois do deletado
            aux[k] = vertices[i];
        }

        delete[] vertices;

        vertices = aux; //Novo vetor sem indices deletados do vetor de vertices

        indices.erase(indices.begin() + scene.at(tab).submesh.startIndex, 
            indices.begin() + scene.at(tab).submesh.startIndex + scene.at(tab).submesh.indexCount); //Tirando o intervalo de indices com Erase

        //Atualizar indices do scene e objLocation
        for (int i{tab}; i < objectsInScene - 1; ++i) {
            objLocation[i] = objLocation[i + 1];
            objLocation[i].baseVertex -= vertexToRemove;
            scene[i] = scene[i + 1];
            scene[i].submesh.baseVertex -= vertexToRemove;
            scene[i].submesh.startIndex -= indexToRemove;
            
        }
        

        //Atualizar objetos em cena
        objectsInScene--;

        delete mesh;
        mesh = new Mesh();

        mesh->VertexBuffer(vertices, newTotalVertex * sizeof(Vertex), sizeof(Vertex));
        mesh->IndexBuffer(indices.data(), newTotalIndex * sizeof(uint), DXGI_FORMAT_R32_UINT);
        mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));
        
        graphics->SubmitCommands();
    }
    
}

void Single::SelectObjectInScene() {
     graphics->ResetCommands();
    
     tab++; //Tab inicia com -1

     if (tab >= objectsInScene) {
        tab = 0;
     }

     static int lastTab = tab - 1; //Ultimo Tab

     if (lastTab > -1) {
         for (int i{}; i < objLocation[lastTab].vertexCount; i++) {
            vertices[objLocation[lastTab].baseVertex + i].color = XMFLOAT4(DirectX::Colors::DimGray);
        }
     }

     for (int i{}; i < objLocation[tab].vertexCount; i++) {
        vertices[objLocation[tab].baseVertex + i].color = XMFLOAT4(DirectX::Colors::Red);
     }

     lastTab = tab;
     //OutputDebugString(std::to_string(tab).c_str());
     mesh->VertexBuffer(vertices, totalVertexCount * sizeof(Vertex), sizeof(Vertex));
     mesh->IndexBuffer(indices.data(), totalIndexCount * sizeof(uint), DXGI_FORMAT_R32_UINT);
     mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));
     graphics->SubmitCommands();
}

void Single::Init()
{
    graphics->ResetCommands();

    // -----------------------------
    // Parâmetros Iniciais da Câmera
    // -----------------------------
 
    // controla rotação da câmera
    theta = XM_PIDIV4;
    phi = 1.3f;
    radius = 5.0f;

    // pega última posição do mouse
    lastMousePosX = (float) input->MouseX();
    lastMousePosY = (float) input->MouseY();

    // inicializa as matrizes Identity e View para a identidade
    Identity = View = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };

    // inicializa a matriz de projeção
    XMStoreFloat4x4(&Proj, XMMatrixPerspectiveFovLH(
        XMConvertToRadians(45.0f), 
        window->AspectRatio(), 
        1.0f, 100.0f));

    // ----------------------------------------
    // Criação da Geometria: Vértices e Índices
    // ----------------------------------------


    Grid grid(3.0f, 3.0f, 20, 20);

    // ---------------------------
    // União de Vértices e Índices
    // ---------------------------

    // quantidade total de vértices
    totalVertexCount = (
        grid.VertexCount()
        );

    //OutputDebugString(std::to_string(totalVertexCount).c_str());

    // tamanho em bytes dos vértices
    const uint vbSize = totalVertexCount * sizeof(Vertex);

    // quantidade total de índices
    totalIndexCount = (
        grid.IndexCount()
        );

    // tamanho em bytes dos índices
    const uint ibSize = totalIndexCount * sizeof(uint);

    // junta todos os vértices em um único vetor
    vertices = new Vertex[totalVertexCount];
    objLocation = new Location[objAmount];
   
    for (uint i = 0; i < grid.VertexCount(); ++i)
    {
        vertices[i].pos = grid.vertices[i].pos;
        vertices[i].color = XMFLOAT4(DirectX::Colors::DimGray);
    }

    objLocation[0] = Location{ 0, (int)grid.VertexCount() }; //BaseVertex e tamanho do objeto
   
    // junta todos os índices em um único vetor
    /*Talvez refazer uma logica propria para vetor de indices*/
    indices.insert(indices.end(), begin(grid.indices), end(grid.indices));

    // ------------------------
    // Definição das Sub-Malhas
    // ------------------------

    // define os parâmetros das sub-malhas
   
    SubMesh gridSubMesh;
    gridSubMesh.indexCount = uint(grid.IndexCount());
    gridSubMesh.startIndex = 0;
    gridSubMesh.baseVertex = 0;
    
    // --------------------
    // Definição de Objetos
    // --------------------

    Object obj;
  
    // grid
    obj.world = Identity;
    obj.cbIndex = 0;
    obj.submesh = gridSubMesh;
    scene.push_back(obj);
    
    // ---------------------------------------------------------------
    // Alocação e Cópia de Vertex, Index e Constant Buffers para a GPU
    // ---------------------------------------------------------------

    // cria malha 3D
    mesh = new Mesh();
    mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
    mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
    mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));
 
    // ---------------------------------------

    BuildRootSignature();
    BuildPipelineState();    

    // ---------------------------------------
    graphics->SubmitCommands();

    timer.Start();
}

// ------------------------------------------------------------------------------

void Single::Update()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Funções de apoio
    {
        if (objectsInScene >= objAmount) { //Crescer vetor de quantidade de objetos em cena e suas localizações

            OutputDebugString("Entrei\n");
            uint newAmount = objAmount * 2;
            Location* aux = new Location[newAmount];
            for (int i{}; i < objAmount; i++) {
                aux[i] = objLocation[i]; //Copiando
            }

            delete[] objLocation;
            objAmount = newAmount;
            string msg = std::to_string(objAmount) + "\n";
            OutputDebugString(msg.c_str());
            objLocation = aux;
        }

        if (input->KeyPress('A')) { //Logs
            OutputDebugString("Logs: \n");
            OutputDebugString("VertexCount: ");
            OutputDebugString(std::to_string(totalVertexCount).c_str());
            OutputDebugString("\n");
            OutputDebugString("IndexCount: ");
            OutputDebugString(std::to_string(totalIndexCount).c_str());
            OutputDebugString("\n");
            OutputDebugString("Scene: \n");
            for (auto& a : scene) {
                OutputDebugString("Index da scene: ");
                OutputDebugString(std::to_string(a.cbIndex).c_str());
                OutputDebugString("\n");
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comandos de adição
    {
        //Adiciona uma BOX ao apertar a tecla B
        if (input->KeyPress('B') || input->KeyPress('b')) {
            Box newBox(2.0f, 2.0f, 2.0f);
            AddObjectToScene(newBox, 0.4f, 0.4f, 0.4f);
        }

        //Tecla C para adicionar Cylinder
        if (input->KeyPress('C') || input->KeyPress('c')) {
            Cylinder newCylinder(1.0f, 0.5f, 3.0f, 20, 10); //Cria novo Cylinder
            AddObjectToScene(newCylinder, 0.5f, 0.5f, 0.5f);
        }

        //Tecla S para adicionar Sphere
        if (input->KeyPress('S') || input->KeyPress('s')) {
            Sphere newSphere(1.0f, 20, 20); //Cria nova Sphere
            AddObjectToScene(newSphere, 0.5f, 0.5f, 0.5f); 
        }
        //Tecla G para adicionar GeoSphere
        if (input->KeyPress('G') || input->KeyPress('g')) {
            GeoSphere newGeoSphere(1.0f, 20); //Cria nova GeoSphere
            AddObjectToScene(newGeoSphere, 0.5f, 0.5f, 0.5f);
        }
        //Tecla P para adicionar Plane(Grid)
        if (input->KeyPress('P') || input->KeyPress('p')) {
            Grid newGrid(3.0f, 3.0f, 20, 20); //Cria novo Grid
            AddObjectToScene(newGrid, 0.5f, 0.5f, 0.5f);
        }
        //Tecla Q para adicionar Quad
        if (input->KeyPress('Q') || input->KeyPress('q')) {
            Quad newQuad(2.0f, 2.0f); //Cria novo Quad
            AddObjectToScene(newQuad, 0.5f, 0.5f, 0.5f);
        }

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Comandas de edição do mundo
    {
        //Tirar tab
        if (input->KeyPress('K') || input->KeyPress('k')) {
            graphics->ResetCommands();
            if (tab != -1) {
                for (int i{}; i < objLocation[tab].vertexCount; i++) {
                    vertices[objLocation[tab].baseVertex + i].color = XMFLOAT4(DirectX::Colors::DimGray);
                }
            }

            tab = -1;

            mesh->VertexBuffer(vertices, totalVertexCount * sizeof(Vertex), sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), totalIndexCount * sizeof(uint), DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));
            graphics->SubmitCommands();
        }

        //Apertar DEL para deletar figura selecionada;
        if (input->KeyPress(VK_DELETE)) {
            OutputDebugString("Entrei\n");
            if(tab > -1)
                DeleteObjectToScene();

        }


        //Tab para selecionar figura
        if (input->KeyPress(VK_TAB)) {
            SelectObjectInScene();
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Derivados
    
        // sai com o pressionamento da tecla ESC
        if (input->KeyPress(VK_ESCAPE))
            window->Close();


        // ativa ou desativa o giro do objeto
        if (input->KeyPress('R') || input->KeyPress('r'))
        {
            spinning = !spinning;

            if (spinning)
                timer.Start();
            else
                timer.Stop();
        }

        float mousePosX = (float)input->MouseX();
        float mousePosY = (float)input->MouseY();

        if (input->KeyDown(VK_LBUTTON))
        {
            // cada pixel corresponde a 1/4 de grau
            float dx = XMConvertToRadians(0.25f * (mousePosX - lastMousePosX));
            float dy = XMConvertToRadians(0.25f * (mousePosY - lastMousePosY));

            // atualiza ângulos com base no deslocamento do mouse 
            // para orbitar a câmera ao redor da caixa
            theta += dx;
            phi += dy;

            // restringe o ângulo de phi ]0-180[ graus
            phi = phi < 0.1f ? 0.1f : (phi > (XM_PI - 0.1f) ? XM_PI - 0.1f : phi);
        }
        else if (input->KeyDown(VK_RBUTTON))
        {
            // cada pixel corresponde a 0.05 unidades
            float dx = 0.05f * (mousePosX - lastMousePosX);
            float dy = 0.05f * (mousePosY - lastMousePosY);

            // atualiza o raio da câmera com base no deslocamento do mouse 
            radius += dx - dy;

            // restringe o raio (3 a 15 unidades)
            radius = radius < 3.0f ? 3.0f : (radius > 15.0f ? 15.0f : radius);
        }

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // converte coordenadas esféricas para cartesianas
        float x = radius * sinf(phi) * cosf(theta);
        float z = radius * sinf(phi) * sinf(theta);
        float y = radius * cosf(phi);

        // constrói a matriz da câmera (view matrix)
        XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
        XMVECTOR target = XMVectorZero();
        XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
        XMStoreFloat4x4(&View, view);

        // carrega matriz de projeção em uma XMMATRIX
        XMMATRIX proj = XMLoadFloat4x4(&Proj);

        // ajusta o buffer constante de cada objeto
        for (auto& obj : scene)
        {
            // carrega matriz de mundo em uma XMMATRIX
            XMMATRIX world = XMLoadFloat4x4(&obj.world);

            // constrói matriz combinada (world x view x proj)
            XMMATRIX WorldViewProj = world * view * proj;

            // atualiza o buffer constante com a matriz combinada
            ObjectConstants constants;
            XMStoreFloat4x4(&constants.WorldViewProj, XMMatrixTranspose(WorldViewProj));
            mesh->CopyConstants(&constants, obj.cbIndex);
        }
    
}

// ------------------------------------------------------------------------------

void Single::Draw()
{
    // limpa o backbuffer
    graphics->Clear(pipelineState);

    // comandos de configuração do pipeline
    ID3D12DescriptorHeap* descriptorHeaps = mesh->ConstantBufferHeap() ;
    graphics->CommandList()->SetDescriptorHeaps(1, &descriptorHeaps); 
    graphics->CommandList()->SetGraphicsRootSignature(rootSignature);
    graphics->CommandList()->IASetVertexBuffers(0, 1, mesh->VertexBufferView());
    graphics->CommandList()->IASetIndexBuffer(mesh->IndexBufferView());
    graphics->CommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    // desenha objetos da cena
    if (objectsInScene > 0) {
        for (auto& obj : scene)
        {
            if (obj.cbIndex != -1) {
                // ajusta o buffer constante associado ao vertex shader
                graphics->CommandList()->SetGraphicsRootDescriptorTable(0, mesh->ConstantBufferHandle(obj.cbIndex));

                // desenha objeto
                graphics->CommandList()->DrawIndexedInstanced(
                    obj.submesh.indexCount, 1,
                    obj.submesh.startIndex,
                    obj.submesh.baseVertex,
                    0);
            }
        }
    }
 
    // apresenta o backbuffer na tela
    graphics->Present();    
}

// ------------------------------------------------------------------------------

void Single::Finalize()
{
    rootSignature->Release();
    pipelineState->Release();
    delete vertices;
    delete mesh;
    delete objLocation;
}


// ------------------------------------------------------------------------------
//                                     D3D                                      
// ------------------------------------------------------------------------------

void Single::BuildRootSignature()
{
    // cria uma única tabela de descritores de CBVs
    D3D12_DESCRIPTOR_RANGE cbvTable = {};
    cbvTable.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    cbvTable.NumDescriptors = 1;
    cbvTable.BaseShaderRegister = 0;
    cbvTable.RegisterSpace = 0;
    cbvTable.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    // define parâmetro raiz com uma tabela
    D3D12_ROOT_PARAMETER rootParameters[1];
    rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
    rootParameters[0].DescriptorTable.pDescriptorRanges = &cbvTable;

    // uma assinatura raiz é um vetor de parâmetros raiz
    D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
    rootSigDesc.NumParameters = 1;
    rootSigDesc.pParameters = rootParameters;
    rootSigDesc.NumStaticSamplers = 0;
    rootSigDesc.pStaticSamplers = nullptr;
    rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    // serializa assinatura raiz
    ID3DBlob* serializedRootSig = nullptr;
    ID3DBlob* error = nullptr;

    ThrowIfFailed(D3D12SerializeRootSignature(
        &rootSigDesc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        &serializedRootSig,
        &error));

    if (error != nullptr)
    {
        OutputDebugString((char*)error->GetBufferPointer());
    }

    // cria uma assinatura raiz com um único slot que aponta para  
    // uma faixa de descritores consistindo de um único buffer constante
    ThrowIfFailed(graphics->Device()->CreateRootSignature(
        0,
        serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&rootSignature)));
}

// ------------------------------------------------------------------------------

void Single::BuildPipelineState()
{
    // --------------------
    // --- Input Layout ---
    // --------------------
    
    D3D12_INPUT_ELEMENT_DESC inputLayout[2] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    // --------------------
    // ----- Shaders ------
    // --------------------

    ID3DBlob* vertexShader;
    ID3DBlob* pixelShader;

    D3DReadFileToBlob(L"Shaders/Vertex.cso", &vertexShader);
    D3DReadFileToBlob(L"Shaders/Pixel.cso", &pixelShader);

    // --------------------
    // ---- Rasterizer ----
    // --------------------

    D3D12_RASTERIZER_DESC rasterizer = {};
    //rasterizer.FillMode = D3D12_FILL_MODE_SOLID;
    rasterizer.FillMode = D3D12_FILL_MODE_WIREFRAME;
    rasterizer.CullMode = D3D12_CULL_MODE_BACK;
    rasterizer.FrontCounterClockwise = FALSE;
    rasterizer.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
    rasterizer.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
    rasterizer.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    rasterizer.DepthClipEnable = TRUE;
    rasterizer.MultisampleEnable = FALSE;
    rasterizer.AntialiasedLineEnable = FALSE;
    rasterizer.ForcedSampleCount = 0;
    rasterizer.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

    // ---------------------
    // --- Color Blender ---
    // ---------------------

    D3D12_BLEND_DESC blender = {};
    blender.AlphaToCoverageEnable = FALSE;
    blender.IndependentBlendEnable = FALSE;
    const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
    {
        FALSE,FALSE,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };
    for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
        blender.RenderTarget[i] = defaultRenderTargetBlendDesc;

    // ---------------------
    // --- Depth Stencil ---
    // ---------------------

    D3D12_DEPTH_STENCIL_DESC depthStencil = {};
    depthStencil.DepthEnable = TRUE;
    depthStencil.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    depthStencil.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    depthStencil.StencilEnable = FALSE;
    depthStencil.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    depthStencil.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
    const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp =
    { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
    depthStencil.FrontFace = defaultStencilOp;
    depthStencil.BackFace = defaultStencilOp;
    
    // -----------------------------------
    // --- Pipeline State Object (PSO) ---
    // -----------------------------------

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso = {};
    pso.pRootSignature = rootSignature;
    pso.VS = { reinterpret_cast<BYTE*>(vertexShader->GetBufferPointer()), vertexShader->GetBufferSize() };
    pso.PS = { reinterpret_cast<BYTE*>(pixelShader->GetBufferPointer()), pixelShader->GetBufferSize() };
    pso.BlendState = blender;
    pso.SampleMask = UINT_MAX;
    pso.RasterizerState = rasterizer;
    pso.DepthStencilState = depthStencil;
    pso.InputLayout = { inputLayout, 2 };
    pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pso.NumRenderTargets = 1;
    pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pso.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    pso.SampleDesc.Count = graphics->Antialiasing();
    pso.SampleDesc.Quality = graphics->Quality();
    graphics->Device()->CreateGraphicsPipelineState(&pso, IID_PPV_ARGS(&pipelineState));

    vertexShader->Release();
    pixelShader->Release();
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    try
    {
        // cria motor e configura a janela
        Engine* engine = new Engine();
        engine->window->Mode(WINDOWED);
        engine->window->Size(1024, 720);
        engine->window->Color(25, 25, 25);
        engine->window->Title("Single");
        engine->window->Icon(IDI_ICON);
        engine->window->Cursor(IDC_CURSOR);
        engine->window->LostFocus(Engine::Pause);
        engine->window->InFocus(Engine::Resume);

        // cria e executa a aplicação
        engine->Start(new Single());

        // finaliza execução
        delete engine;
    }
    catch (Error & e)
    {
        // exibe mensagem em caso de erro
        MessageBox(nullptr, e.ToString().data(), "Single", MB_OK);
    }

    return 0;
}

// ----------------------------------------------------------------------------

