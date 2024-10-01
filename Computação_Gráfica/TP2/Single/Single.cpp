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
    int beginVertex;
    int endVertex;
    int beginIndex;
    int endIndex;
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

    void BuildRootSignature();
    void BuildPipelineState();
};

// ------------------------------------------------------------------------------

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
    objLocation[0].beginVertex = 0; //Inicio do primeiro obj no vetor de vertices
    for (uint i = 0; i < grid.VertexCount(); ++i)
    {
        vertices[i].pos = grid.vertices[i].pos;
        vertices[i].color = XMFLOAT4(DirectX::Colors::DimGray);
    }

    objLocation[0].endVertex = totalVertexCount; //Fim do objeto no vetor de vertices
    
   
    // junta todos os índices em um único vetor
    /*Refazer uma logica propria para vetor de indices*/
    objLocation[0].beginIndex = 0; //Indice começa no começo do vector de indices
    indices.insert(indices.end(), begin(grid.indices), end(grid.indices));
    objLocation[0].endIndex = indices.size(); //Termina sempre no final
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
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comandos de adição
    {
        //Adiciona uma BOX ao apertar a tecla B
        if (input->KeyPress('B') || input->KeyPress('b')) {
            graphics->ResetCommands();

            Box newBox(2.0f, 2.0f, 2.0f); //Cria BOX

            uint newTotalVertexCount = totalVertexCount + newBox.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newBox.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newBox.VertexCount(); i++, k++) {
                aux[k].pos = newBox.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;
            
            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newBox.indices), end(newBox.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newBoxSubMesh; //Definindo subMalha
            newBoxSubMesh.indexCount = uint(newBox.IndexCount());
            newBoxSubMesh.startIndex = totalIndexCount;
            newBoxSubMesh.baseVertex = totalVertexCount;

            //Definição do Objeto
            Object obj;

            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.4f, 0.4f, 0.4f) *
                XMMatrixTranslation(0.0f, 0.0f, 0.0f));
            obj.cbIndex = objectsInScene; //Recebe numero de objetos *COMEÇA COM UM POR JA INICIAR COM O GRID*
            obj.submesh = newBoxSubMesh; //Recebe submalha da nova BOX
            scene.push_back(obj); //Coloca no vetor

            objectsInScene++; //Atualiza quantidade de objetos na cena

            //Alocação e Cópia de Vertex, Index e Constant Buffers para a GPU
            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            // ---------------------------------------

            graphics->SubmitCommands();

        }

        //Tecla C para adicionar Cylinder
        if (input->KeyPress('C') || input->KeyPress('c')) {
            graphics->ResetCommands();

            Cylinder newCylinder(1.0f, 0.5f, 3.0f, 20, 10); //Cria novo Cylinder

            uint newTotalVertexCount = totalVertexCount + newCylinder.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newCylinder.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newCylinder.VertexCount(); i++, k++) {
                aux[k].pos = newCylinder.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;

            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newCylinder.indices), end(newCylinder.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newCylinderSubMesh;
            newCylinderSubMesh.indexCount = uint(newCylinder.IndexCount());
            newCylinderSubMesh.startIndex = totalIndexCount;
            newCylinderSubMesh.baseVertex = totalVertexCount;

            Object obj;
            // cylinder
            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.5f, 0.5f, 0.5f) *
                XMMatrixTranslation(0.0f, 0.0f, 0.0f));
            obj.cbIndex = objectsInScene;
            obj.submesh = newCylinderSubMesh;
            scene.push_back(obj);

            objectsInScene++;

            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            graphics->SubmitCommands();
        }

        //Tecla S para adicionar Sphere
        if (input->KeyPress('S') || input->KeyPress('s')) {
            graphics->ResetCommands();

            Sphere newSphere(1.0f, 20, 20); //Cria nova Sphere

            uint newTotalVertexCount = totalVertexCount + newSphere.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newSphere.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newSphere.VertexCount(); i++, k++) {
                aux[k].pos = newSphere.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;

            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newSphere.indices), end(newSphere.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newSphereSubMesh;
            newSphereSubMesh.indexCount = uint(newSphere.IndexCount());
            newSphereSubMesh.startIndex = totalIndexCount;
            newSphereSubMesh.baseVertex = totalVertexCount;

            Object obj;
            // Sphere
            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.5f, 0.5f, 0.5f) *
                XMMatrixTranslation(0.0f, 0.0f, 0.0f));
            obj.cbIndex = objectsInScene;
            obj.submesh = newSphereSubMesh;
            scene.push_back(obj);

            objectsInScene++;

            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            graphics->SubmitCommands();
        }
        //Tecla G para adicionar GeoSphere
        if (input->KeyPress('G') || input->KeyPress('g')) {
            graphics->ResetCommands();

            GeoSphere newGeoSphere(1.0f, 20); //Cria nova GeoSphere

            uint newTotalVertexCount = totalVertexCount + newGeoSphere.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newGeoSphere.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newGeoSphere.VertexCount(); i++, k++) {
                aux[k].pos = newGeoSphere.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;

            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newGeoSphere.indices), end(newGeoSphere.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newGeoSphereSubMesh;
            newGeoSphereSubMesh.indexCount = uint(newGeoSphere.IndexCount());
            newGeoSphereSubMesh.startIndex = totalIndexCount;
            newGeoSphereSubMesh.baseVertex = totalVertexCount;

            Object obj;
            // GeoSphere
            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.5f, 0.5f, 0.5f) *
                XMMatrixTranslation(0.0f, 0.0f, 0.0f));
            obj.cbIndex = objectsInScene;
            obj.submesh = newGeoSphereSubMesh;
            scene.push_back(obj);

            objectsInScene++;

            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            graphics->SubmitCommands();
        }
        //Tecla P para adicionar Plane(Grid)
        if (input->KeyPress('P') || input->KeyPress('p')) {
            graphics->ResetCommands();

            Grid newGrid(3.0f, 3.0f, 20, 20); //Cria novo Grid

            uint newTotalVertexCount = totalVertexCount + newGrid.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newGrid.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newGrid.VertexCount(); i++, k++) {
                aux[k].pos = newGrid.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;

            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newGrid.indices), end(newGrid.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newGridSubMesh;
            newGridSubMesh.indexCount = uint(newGrid.IndexCount());
            newGridSubMesh.startIndex = totalIndexCount;
            newGridSubMesh.baseVertex = totalVertexCount;

            Object obj;
            // Grid
            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.5f, 0.5f, 0.5f)*
                XMMatrixTranslation(0.0f, 0.5f, 0.0f));
            obj.cbIndex = objectsInScene;
            obj.submesh = newGridSubMesh;
            scene.push_back(obj);

            objectsInScene++;

            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            graphics->SubmitCommands();
        }
        //Tecla Q para adicionar Quad
        if (input->KeyPress('Q') || input->KeyPress('q')) {
            graphics->ResetCommands();

            Quad newQuad(2.0f, 2.0f); //Cria novo Quad

            uint newTotalVertexCount = totalVertexCount + newQuad.VertexCount(); //Calcula quantidade de novos vertices

            const uint vbSize = newTotalVertexCount * sizeof(Vertex); //Calcula vbSize nova

            uint newTotalIndexCount = totalIndexCount + newQuad.IndexCount(); //Calcula quantidade novos indices

            const uint ibSize = newTotalIndexCount * sizeof(uint); //Calcula ibsize nova

            Vertex* aux = new Vertex[newTotalVertexCount]; //Cria um novo vetor aux;
            int k = 0;
            objLocation[objectsInScene].beginVertex = totalVertexCount;
            for (uint i{}; i < totalVertexCount; i++, k++) { //Copia dados do vetor antigo
                aux[i].pos = vertices[i].pos;
                aux[i].color = vertices[i].color;
            }

            for (uint i{}; i < newQuad.VertexCount(); i++, k++) {
                aux[k].pos = newQuad.vertices[i].pos;
                aux[k].color = XMFLOAT4(DirectX::Colors::DimGray);
            }
            objLocation[objectsInScene].endVertex = newTotalVertexCount;

            objLocation[objectsInScene].beginIndex = indices.size();
            indices.insert(indices.end(), begin(newQuad.indices), end(newQuad.indices)); //Insere em vector de indices
            objLocation[objectsInScene].endIndex = indices.size();

            SubMesh newQuadSubMesh;
            newQuadSubMesh.indexCount = uint(newQuad.IndexCount());
            newQuadSubMesh.startIndex = totalIndexCount;
            newQuadSubMesh.baseVertex = totalVertexCount;

            Object obj;
            // Quad
            XMStoreFloat4x4(&obj.world,
                XMMatrixScaling(0.5f, 0.5f, 0.5f) *
                XMMatrixTranslation(0.0f, 0.0f, 0.0f));
            obj.cbIndex = objectsInScene;
            obj.submesh = newQuadSubMesh;
            scene.push_back(obj);

            objectsInScene++;

            delete[] vertices;

            totalVertexCount = newTotalVertexCount;
            totalIndexCount = newTotalIndexCount;

            //OutputDebugString(std::to_string(totalVertexCount).c_str());

            vertices = aux;

            //mesh = new Mesh();
            mesh->VertexBuffer(vertices, vbSize, sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), ibSize, DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

            graphics->SubmitCommands();
        }

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Comandas de edição do mundo
    {
        //Tirar tab
        if (input->KeyPress('K') || input->KeyPress('k')) {
            graphics->ResetCommands();
            if (tab != -1) {
                for (int i = objLocation[tab].beginVertex; i < objLocation[tab].endVertex; i++) {
                    vertices[i].color = XMFLOAT4(DirectX::Colors::DimGray);
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

            if (tab != -1 && objectsInScene > 0) {
                graphics->ResetCommands();

                
                int newTotalVertexCount = totalVertexCount - (objLocation[tab].endVertex - objLocation[tab].beginVertex);
                int newTotalIndexCount = totalIndexCount - (objLocation[tab].endIndex - objLocation[tab].beginIndex);
                //Fazendo uma copia para um vetor de todos menos os deletados;
                Vertex* aux = new Vertex[newTotalVertexCount];

                //Iniciando de for que vai até o inicio do que desejamos deletar
                int k = 0;
                for (int i{}; i < objLocation[tab].beginVertex; i++, k++) {
                    aux[k] = vertices[i];
                }

                for (int i{objLocation[tab].endVertex}; i < totalVertexCount; i++, k++) { //For que vai do fim do deletado ate o fim do vetor total
                    aux[k] = vertices[i];
                }


                delete[] vertices;
                vertices = aux;
                
                indices.erase(indices.begin() + objLocation[tab].beginIndex, //Inicio do intervalo
                    indices.begin() + objLocation[tab].endIndex); //Fim do intervalo

                scene.erase(scene.begin() + tab);

                for (int i{ tab }; i < scene.size(); i++) {
                    if (scene.at(i).cbIndex != 0) {
                        scene.at(i).cbIndex -= 1;
                    }
                }

                tab = -1;

                totalVertexCount = newTotalVertexCount;
                totalIndexCount = newTotalIndexCount;

                // Atualizar os buffers na GPU
                mesh->VertexBuffer(vertices, totalVertexCount * sizeof(Vertex), sizeof(Vertex));
                mesh->IndexBuffer(indices.data(), totalIndexCount * sizeof(uint), DXGI_FORMAT_R32_UINT);
                mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));

                // Submeter os novos comandos
                graphics->SubmitCommands();
            }
        }


        //Tab para selecionar figura
        if (input->KeyPress(VK_TAB)) {
            graphics->ResetCommands();
            static int lastTab = tab - 1;

            //OutputDebugString("Entrei");
            tab++;
            if (tab >= objectsInScene) {
                tab = 0;
            }

            if (lastTab != -1) {
                for (int i = objLocation[lastTab].beginVertex; i < objLocation[lastTab].endVertex; i++) {
                    vertices[i].color = XMFLOAT4(DirectX::Colors::DimGray);
                }
            }

            for (int i = objLocation[tab].beginVertex; i < objLocation[tab].endVertex; i++) {
                vertices[i].color = XMFLOAT4(DirectX::Colors::Red);
            }

            lastTab = tab;
            //OutputDebugString(std::to_string(tab).c_str());
            mesh->VertexBuffer(vertices, totalVertexCount * sizeof(Vertex), sizeof(Vertex));
            mesh->IndexBuffer(indices.data(), totalIndexCount * sizeof(uint), DXGI_FORMAT_R32_UINT);
            mesh->ConstantBuffer(sizeof(ObjectConstants), uint(scene.size()));
            graphics->SubmitCommands();
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
    for (auto& obj : scene)
    {
        // ajusta o buffer constante associado ao vertex shader
        graphics->CommandList()->SetGraphicsRootDescriptorTable(0, mesh->ConstantBufferHandle(obj.cbIndex));

        // desenha objeto
        graphics->CommandList()->DrawIndexedInstanced(
            obj.submesh.indexCount, 1,
            obj.submesh.startIndex,
            obj.submesh.baseVertex,
            0);
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

