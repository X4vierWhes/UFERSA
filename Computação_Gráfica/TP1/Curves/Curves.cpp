/**********************************************************************************
// Triangle (C�digo Fonte)
//
// Cria��o:     22 Jul 2020
// Atualiza��o: 30 Jul 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Constr�i um Tri�ngulo usando o Direct3D 12
//
**********************************************************************************/

#include "DXUT.h"
#include <vector>
#include <fstream>

// ------------------------------------------------------------------------------

struct Vertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

struct Point {
    float x;
    float y;
};

// ------------------------------------------------------------------------------

class Curves : public App
{
private:
    ID3D12RootSignature* rootSignature;
    ID3D12PipelineState* pipelineState;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*AREA QUE CUIDA DO ICONE*/
    Mesh* geometry; //Geometria do icone;

    // quantidade de v�rtices na geometria
    static const uint VertexCount = 6;
    // v�rtices da geometria
    Vertex vertices[VertexCount] =
    {
        { XMFLOAT3(-0.02f, 0.02f, 0.0f), XMFLOAT4(Colors::Purple) },
        { XMFLOAT3(0.02f, 0.02f, 0.0f), XMFLOAT4(Colors::Purple) },
        { XMFLOAT3(0.02f, -0.02f, 0.0f), XMFLOAT4(Colors::Purple) },
        { XMFLOAT3(0.02f, -0.02f, 0.0f), XMFLOAT4(Colors::Purple) },
        { XMFLOAT3(-0.02f, -0.02f, 0.0f), XMFLOAT4(Colors::Purple) },
        { XMFLOAT3(-0.02f, 0.02f, 0.0f), XMFLOAT4(Colors::Purple) }
    };

    Point vertexPoints[VertexCount] = {
        {-0.02f, 0.02f},
        {0.02f, 0.02f},
        {0.02f, -0.02f},
        {0.02f, -0.02f},
        {-0.02f, -0.02f},
        {-0.02f, 0.02f}
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*AREA QUE CUIDA DAS CURVAS*/
    Mesh* curvesMesh; //Geometria das curvas
    uint curvesCount = 0; //Quantidade de curvas no vetor
    static const uint curvesPoints = 20; //Quantidade de pontos para fazer a curva
    int amount = 400; //Tamanho inicial do vetor
    Vertex* curves; //Vetor dinamico
    //std::vector<Vertex> curves; //vetor de curvas
    Point pointsLocation[4]{}; //Pontos do clique

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*AREA QUE CUIDA DOS PONTOS DE CONTROLE DESENHANDOS NA TELA*/
    Mesh* pointsMesh; //Geometria pontos de controle
    static const uint ctrlCount = 4; //Quantidade de vertices de controle;
    Vertex points[ctrlCount][VertexCount]{};
    int pointsCount = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*AREA QUE CUIDA DAS LINHAS DE CONTROLE*/
    Mesh* linesMesh; //Geometria das linhas de controle
    Vertex lines[ctrlCount]{}; //Vetor que cuidar� das linhas de controle

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*AREA QUE CUIDA DA LINHA QUE SEGUE O MOUSE*/
    Mesh* lineMesh; //Linha que segue o mouse
    static const uint lineCount = 2;
    Vertex linee[lineCount]{};

public:
    void Init();
    void Update();
    void Display();
    void Finalize();

    
    float Bernstein(float, float, float, float, float);

    void BuildRootSignature();
    void BuildPipelineState();
};

// ------------------------------------------------------------------------------

float Curves::Bernstein(float num, float p1, float p2, float p3, float p4) {
    return (1 - num) * (1 - num) * (1 - num) * p1 + (3 * num) * (1 - num) * (1 - num) * p2
        + 3 * (num * num) * (1 - num) * p3 + (num * num * num) * p4;
}

void Curves::Init()
{
    graphics->ResetCommands();

    // ---------[ Build Geometry ]------------

    // tamanho do buffer de v�rtices em bytes
    const uint vbSize = VertexCount * sizeof(Vertex);

    // cria malha 3D
    geometry = new Mesh(vertices, vbSize, sizeof(Vertex));
    curvesMesh = new Mesh(&curves, (amount * sizeof(Vertex)), sizeof(Vertex));
    pointsMesh = new Mesh(points, (ctrlCount*VertexCount * sizeof(Vertex)), sizeof(Vertex));
    linesMesh = new Mesh(lines, (ctrlCount * sizeof(Vertex)), sizeof(Vertex));
    lineMesh = new Mesh(linee, lineCount * sizeof(Vertex), (uint)sizeof(Vertex));
    // -----------------------
    //Vetor dinamico de curvas
    curves = new Vertex[amount];

    BuildRootSignature();
    BuildPipelineState();

    // -----------------------
    graphics->SubmitCommands();
}

// ------------------------------------------------------------------------------

void Curves::Update()
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*Posi��o do mouse*/

    float cx = float(window->CenterX());
    float cy = float(window->CenterY());
    float mx = float(input->MouseX());
    float my = float(input->MouseY());

    float x = ((mx - cx) / cx);
    float y = ((cy - my) / cy);

    ////////////////////////////////////////////////////////////////////////////////////
    /*Reinicializa��o dos pontos e linhas de controle*/
    if (pointsCount == 4) {
        //"Excluindo" primeiros dois pontos e mantendo somente os dois ultimos
     
        for (int i{}; i < VertexCount; i++) {
            points[1][i].Pos.x = points[3][i].Pos.x + (points[3][i].Pos.x - points[2][i].Pos.x);
            points[1][i].Pos.y = points[3][i].Pos.y + (points[3][i].Pos.y - points[2][i].Pos.y);
            points[0][i].Pos.x = points[3][i].Pos.x;
            points[0][i].Pos.y = points[3][i].Pos.y;
        }

        //"Excluindo" as primeiras duas linhas e mantendo somente as duas ultimas e tamb�m continuando ela com a formula p4 = p4 + (p4-p3);
        lines[0] = lines[3];
        lines[1].Pos.x = lines[3].Pos.x + (lines[3].Pos.x - lines[2].Pos.x);
        lines[1].Pos.y = lines[3].Pos.y + (lines[3].Pos.y - lines[2].Pos.y);
        pointsCount = 2;

        //"Excluindo" primeiros dois pontos e mantendo somente os dois ultimos;
        pointsLocation[0] = pointsLocation[3];
        pointsLocation[1].x = pointsLocation[3].x + (pointsLocation[3].x - pointsLocation[2].x);
        pointsLocation[1].y = pointsLocation[3].y + (pointsLocation[3].y - pointsLocation[2].y);
        
        //Mudando ponteiro da linha que segue o mouse;
        linee[0] = { XMFLOAT3(pointsLocation[1].x, pointsLocation[1].y, 0.0f), XMFLOAT4(Colors::DarkViolet) };
        //Mandando comandos de desenho para o buffer;
        graphics->ResetCommands();
        graphics->Copy(points, pointsMesh->vertexBufferSize, pointsMesh->vertexBufferUpload, pointsMesh->vertexBufferGPU);
        graphics->SubmitCommands();

        graphics->ResetCommands();
        graphics->Copy(lines, linesMesh->vertexBufferSize, linesMesh->vertexBufferUpload, linesMesh->vertexBufferGPU);
        graphics->SubmitCommands();
        
        curvesCount+= 20;

        if (curvesCount >= amount) {
            if (amount * 2 <= 25600) {
                //Crescendo vetor dinamico;
                int newAmount = amount * 2;
                Vertex* aux = new Vertex[newAmount];
                
                for (int i{}; i < curvesCount; i++) {
                    aux[i] = curves[i]; //Copiando;
                }

                delete[] curves; //Deleta vetor atual;

                amount = newAmount; //Novo tamanho;

                curves = aux; //Ponteiro aponta para auxiliar;

                delete curvesMesh; //Deleta a mesh antiga;

                curvesMesh = new Mesh(&curves, (amount * sizeof(Vertex)), sizeof(Vertex)); //Cria nova mesh com novo tamanho;

                //Atualiza comandos para o buffer;
                graphics->ResetCommands();
                graphics->Copy(curves, curvesMesh->vertexBufferSize, curvesMesh->vertexBufferUpload, curvesMesh->vertexBufferGPU);
                graphics->SubmitCommands();
            }
            else {
                curvesCount = 25580; //Limite de crescimento alcan�ado, vetor n�o cresce mais;
            }
            //curvesCount = 380;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*Cria��o das curvas*/
    if (pointsCount > 1) {  //Ultimos 2 pontos seguirem o mouse;
        if (pointsCount == 2) {
            pointsLocation[2] = pointsLocation[3] = { x, y };
        }
        else if (pointsCount == 3){
            pointsLocation[3] = { x, y };
        }
     }

    //Curva aparecer ap�s segundo clique;
    if (pointsCount > 1) {
        
        for (int i{}; i < curvesPoints; i++) {
            curves[i+curvesCount] = {
             XMFLOAT3(Bernstein(i / 20.0, pointsLocation[0].x, pointsLocation[1].x,
             pointsLocation[2].x, pointsLocation[3].x),
             Bernstein(i / 20.0, pointsLocation[0].y, pointsLocation[1].y,
             pointsLocation[2].y, pointsLocation[3].y), 0.0f),
             XMFLOAT4(Colors::Yellow)
            };
        }
        
        graphics->ResetCommands();
        graphics->Copy(curves, curvesMesh->vertexBufferSize, curvesMesh->vertexBufferUpload, curvesMesh->vertexBufferGPU);
        graphics->SubmitCommands();
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*Movimenta��o do icone*/

    for (int i{}; i < VertexCount; i++) {
        vertices[i].Pos.x = x + vertexPoints[i].x;
        vertices[i].Pos.y = y + vertexPoints[i].y;
    }

    graphics->ResetCommands();
    graphics->Copy(vertices, geometry->vertexBufferSize, geometry->vertexBufferUpload, geometry->vertexBufferGPU);
    graphics->SubmitCommands();  
    
    if (pointsCount >= 1 && pointsCount <= 3) {
        linee[1] = { XMFLOAT3(x, y, 0.0f), XMFLOAT4(Colors::DarkViolet)};

        graphics->ResetCommands();
        graphics->Copy(linee, lineMesh->vertexBufferSize, lineMesh->vertexBufferUpload, lineMesh->vertexBufferGPU);
        graphics->SubmitCommands();
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*Comandos do teclado*/


    //Clique do mouse coloca pontos
    if (input->KeyPress(VK_LBUTTON)) {
        //Colocando pontos de controle

        if (pointsCount >= 0 && pointsCount <= 3) { //Index 0 ate 3
            //Pontos saem aqui
            for (int i{}; i < VertexCount; i++) {
                points[pointsCount][i].Pos.x = x + vertexPoints[i].x;
                points[pointsCount][i].Pos.y = y + vertexPoints[i].y;

                points[pointsCount][i].Color = { XMFLOAT4(Colors::Purple) };
            }

            pointsLocation[pointsCount] = { x, y };

            graphics->ResetCommands();
            graphics->Copy(points, pointsMesh->vertexBufferSize, pointsMesh->vertexBufferUpload, pointsMesh->vertexBufferGPU);
            graphics->SubmitCommands();

            lines[pointsCount] = { XMFLOAT3(x, y, 0.0f), XMFLOAT4(Colors::DarkViolet) };
            linee[0] = { XMFLOAT3(x, y, 0.0f), XMFLOAT4(Colors::DarkViolet) };

            graphics->ResetCommands();
            graphics->Copy(lines, linesMesh->vertexBufferSize, linesMesh->vertexBufferUpload, linesMesh->vertexBufferGPU);
            graphics->SubmitCommands();

            pointsCount++;
        }
       
    }

    //Exclus�o de curvas
    if (input->KeyPress(VK_DELETE) || input->KeyPress('d') || input->KeyPress('D')) {
        pointsCount = 0;
        curvesCount = 0;
        delete[] curves;
        curves = new Vertex[amount];

        //Mandando comandos de desenho para o buffer
        graphics->ResetCommands();
        graphics->Copy(points, pointsMesh->vertexBufferSize, pointsMesh->vertexBufferUpload, pointsMesh->vertexBufferGPU);
        graphics->SubmitCommands();

        graphics->ResetCommands();
        graphics->Copy(lines, linesMesh->vertexBufferSize, linesMesh->vertexBufferUpload, linesMesh->vertexBufferGPU);
        graphics->SubmitCommands();

        graphics->ResetCommands();
        graphics->Copy(curves, curvesMesh->vertexBufferSize, curvesMesh->vertexBufferUpload, curvesMesh->vertexBufferGPU);
        graphics->SubmitCommands();
    }

    // sai com o pressionamento da tecla ESC
    if (input->KeyPress(VK_ESCAPE))
        window->Close();

    //Salvar dados em arquivo
    if (input->KeyPress('s') || input->KeyPress('S')) {
         std::ofstream arquivo("savedata.bin", std::ios::binary);

         if (arquivo.is_open()) {

             arquivo.write(reinterpret_cast<const char*>(&amount), sizeof(int)); //Escreve tamanho atual do vetor;
             arquivo.write(reinterpret_cast<const char*>(&curvesCount), sizeof(int)); //Escreve quantidade de curvas no vetor;
             

             for (int i{}; i < ctrlCount; i++) {
                 arquivo.write(reinterpret_cast<const char*>(&lines[i]), sizeof(Vertex));  //Escreve linhas no arquivo;
             }

             arquivo.write(reinterpret_cast<const char*>(&pointsCount), sizeof(int)); //Escreve quantidade de pontos atuais;

             for (int i{}; i < ctrlCount; i++) {
                 for (int j{}; j < VertexCount; j++) {
                    arquivo.write(reinterpret_cast<const char*>(&points[i][j]), sizeof(Vertex));  //Escreve pontos
                 }
             }

             for (int i{}; i < ctrlCount; i++) {
                 arquivo.write(reinterpret_cast<const char*>(&pointsLocation[i]), sizeof(Point));  //Escreve localiza��o dos pontos
             }


             for (int i{}; i < 2; i++) {
                 arquivo.write(reinterpret_cast<const char*>(&linee[i]), sizeof(Vertex));  //Escreve localiza��o dos pontos
             }

             for (int i{}; i < curvesCount; i++) {
                 arquivo.write(reinterpret_cast<const char*>(&curves[i]), sizeof(Vertex)); //Escreve curvas;
             }

             arquivo.close();
         }
    }

    //Carregar dados do arquivo
    if (input->KeyPress('l') || input->KeyPress('L')) {
        std::ifstream arquivo("savedata.bin", std::ios::binary);

        if (arquivo) {
            int i = 0;

            // Leitura da quantidade total de curvas e inicializa��o do vetor de curvas
            arquivo.read(reinterpret_cast<char*>(&amount), sizeof(int));
            curves = new Vertex[amount];

            // Leitura da quantidade de curvas ativas
            arquivo.read(reinterpret_cast<char*>(&curvesCount), sizeof(int));

            // Leitura das linhas de controle
            for (i = 0; i < ctrlCount; i++) {
                arquivo.read(reinterpret_cast<char*>(&lines[i]), sizeof(Vertex));
            }

            // Leitura da quantidade de pontos
            arquivo.read(reinterpret_cast<char*>(&pointsCount), sizeof(int));

            // Leitura dos pontos
            for (i = 0; i < ctrlCount; i++) {
                for (int j = 0; j < VertexCount; j++) {
                    arquivo.read(reinterpret_cast<char*>(&points[i][j]), sizeof(Vertex));
                }
            }

            // Leitura das localiza��es dos pontos
            for (i = 0; i < ctrlCount; i++) {
                arquivo.read(reinterpret_cast<char*>(&pointsLocation[i]), sizeof(Point));
            }

            for (int i{}; i < 2; i++) {
                arquivo.read(reinterpret_cast<char*>(&linee[i]), sizeof(Vertex));  //Escreve localiza��o dos pontos
            }

            // Leitura das curvas
            for (i = 0; i < curvesCount; i++) {
                arquivo.read(reinterpret_cast<char*>(&curves[i]), sizeof(Vertex));
            }

            curvesMesh = new Mesh(&curves, (amount * sizeof(Vertex)), sizeof(Vertex));

            arquivo.close();

            //Mandando comandos de desenho para o buffer
            graphics->ResetCommands();
            graphics->Copy(points, pointsMesh->vertexBufferSize, pointsMesh->vertexBufferUpload, pointsMesh->vertexBufferGPU);
            graphics->SubmitCommands();

            graphics->ResetCommands();
            graphics->Copy(lines, linesMesh->vertexBufferSize, linesMesh->vertexBufferUpload, linesMesh->vertexBufferGPU);
            graphics->SubmitCommands();

            graphics->ResetCommands();
            graphics->Copy(curves, curvesMesh->vertexBufferSize, curvesMesh->vertexBufferUpload, curvesMesh->vertexBufferGPU);
            graphics->SubmitCommands();

            graphics->ResetCommands();
            graphics->Copy(linee, lineMesh->vertexBufferSize, lineMesh->vertexBufferUpload, lineMesh->vertexBufferGPU);
            graphics->SubmitCommands();

        }
    }  

    Display();
}

// ------------------------------------------------------------------------------

void Curves::Display()
{
    // limpa backbuffer
    graphics->Clear(pipelineState);

    // submete comandos de configura��o do pipeline
    graphics->CommandList()->SetGraphicsRootSignature(rootSignature);

    //Desenha icone;
    graphics->CommandList()->IASetVertexBuffers(0, 1, geometry->VertexBufferView());
    graphics->CommandList()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // submete comando de desenho
    graphics->CommandList()->DrawInstanced(6, 1, 0, 0);

    //Desenha pontos de controle
    graphics->CommandList()->IASetVertexBuffers(0, 1, pointsMesh->VertexBufferView());
    graphics->CommandList()->DrawInstanced(6 * pointsCount, 1, 0, 0);

    //Desenha linhas de controle
    graphics->CommandList()->IASetVertexBuffers(0, 1, linesMesh->VertexBufferView());
    graphics->CommandList()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
    graphics->CommandList()->DrawInstanced(pointsCount, 1, 0, 0);

    //Desenha linha que segue mouse
    graphics->CommandList()->IASetVertexBuffers(0, 1, lineMesh->VertexBufferView());
    graphics->CommandList()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
    if (pointsCount >= 1) {
        graphics->CommandList()->DrawInstanced(lineCount, 1, 0, 0);
    }

    //Desenha a curva;
    graphics->CommandList()->IASetVertexBuffers(0, 1, curvesMesh->VertexBufferView());
    graphics->CommandList()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
    graphics->CommandList()->DrawInstanced(amount, 1, 0, 0);
    
    // apresenta backbuffer
    graphics->Present();
}

// ------------------------------------------------------------------------------

void Curves::Finalize()
{
    rootSignature->Release();
    pipelineState->Release();
    delete geometry;
    delete pointsMesh;
    delete linesMesh;
    delete curvesMesh;
    delete lineMesh;
    delete curves;
}


// ------------------------------------------------------------------------------
//                                     D3D                                      
// ------------------------------------------------------------------------------

void Curves::BuildRootSignature()
{
    // descri��o para uma assinatura vazia
    D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
    rootSigDesc.NumParameters = 0;
    rootSigDesc.pParameters = nullptr;
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

    // cria uma assinatura raiz vazia
    ThrowIfFailed(graphics->Device()->CreateRootSignature(
        0,
        serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&rootSignature)));
}

// ------------------------------------------------------------------------------

void Curves::BuildPipelineState()
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
    rasterizer.FillMode = D3D12_FILL_MODE_SOLID;
    //rasterizer.FillMode = D3D12_FILL_MODE_WIREFRAME;
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
        engine->window->Size(600, 600);
        engine->window->ResizeMode(ASPECTRATIO);
        engine->window->Color(0, 0, 0);
        engine->window->Title("Triangle");
        engine->window->Icon(IDI_ICON);
        engine->window->LostFocus(Engine::Pause);
        engine->window->InFocus(Engine::Resume);

        // cria e executa a aplica��o
        engine->Start(new Curves());

        // finaliza execu��o
        delete engine;
    }
    catch (Error& e)
    {
        // exibe mensagem em caso de erro
        MessageBox(nullptr, e.ToString().data(), "Triangle", MB_OK);
    }

    return 0;
}

// ----------------------------------------------------------------------------