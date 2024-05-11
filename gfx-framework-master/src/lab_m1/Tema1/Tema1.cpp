#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    //initializarea variabilelor
    {
        //laturi, lungimi
        move = 130;
        squareSide = 100;
        lengthRomb = squareSide / 5;
        lengthStea = 4 * lengthRomb;
        lengthHexa = 2 * lengthRomb;

        //colturi
        corner = glm::vec3(0, 0, 0);
        cornerUpRight = glm::vec3(resolution.x, resolution.y, 0);
        cornerUpLeft = glm::vec3(0, resolution.y, 0);
        middleOfScreen = glm::vec3((float)resolution.x / 2, (float)resolution.y / 2, 0);
        offScreen = glm::vec3(resolution.x + lengthHexa, move / 5 + squareSide / 2, 0);

        //variabile pentru translatie, rotatie si scalare
        translateX_hexaR = translateX_stea = 0;
        scaleX_romb = scaleY_romb = scaleX_hexaR = scaleY_hexaR = scaleX_hexaP = scaleY_hexaP = 1;
        angularStep = 0;

        //variabile pentru anumite evenimente (apasarea unui buton)
        rombDispare = false;
        hexaDispareR = hexaDispareP = false;
        leftMouse = 0;
    }

    //romburi
    {
        Mesh* rombR = object2D::CreateRomb("rombR", cornerUpLeft, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(rombR);
        Mesh* rombP = object2D::CreateRomb("rombP", cornerUpLeft, lengthRomb, glm::vec3(1, 0.5, 0), true);
        AddMeshToList(rombP);
        Mesh* rombA = object2D::CreateRomb("rombA", cornerUpLeft, lengthRomb, glm::vec3(0, 0, 1), true);
        AddMeshToList(rombA);
        Mesh* rombM = object2D::CreateRomb("rombM", cornerUpLeft, lengthRomb, glm::vec3(1, 0, 1), true);
        AddMeshToList(rombM);
    }

    Mesh* square = object2D::CreateSquare("square", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square);

    Mesh* squareRomb = object2D::CreateSquare("squareRomb", cornerUpLeft, squareSide, glm::vec3(0, 0, 0), false);
    AddMeshToList(squareRomb);

    Mesh* squareHealth = object2D::CreateSquare("squareHealth", cornerUpRight, squareSide * 3 / 4, glm::vec3(1, 0, 0), true);
    AddMeshToList(squareHealth);

    Mesh* health = object2D::CreateSquare("health", corner, squareSide * 2 / 3, glm::vec3(1, 0, 0), true);
    AddMeshToList(health);

    Mesh* stea = object2D::CreateStea("stea", corner, lengthStea, glm::vec3(1, 0, 0), true);
    AddMeshToList(stea);

    //hexagoane
    {
        Mesh* hexaR = object2D::CreateHexagon("hexaR", corner, lengthHexa, glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), true);
        AddMeshToList(hexaR);

        Mesh* hexaP = object2D::CreateHexagon("hexaP", corner, lengthHexa, glm::vec3(1, 0.5, 0), glm::vec3(1, 0, 1), true);
        AddMeshToList(hexaP);

        Mesh* hexaA = object2D::CreateHexagon("hexaA", corner, lengthHexa, glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), true);
        AddMeshToList(hexaA);

        Mesh* hexaM = object2D::CreateHexagon("hexaM", corner, lengthHexa, glm::vec3(1, 0, 1), glm::vec3(1, 0.5, 0), true);
        AddMeshToList(hexaM);
    }

    //romburi pe patratele
    {
        Mesh* romb1 = object2D::CreateRomb("romb1", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb1);

        Mesh* romb2 = object2D::CreateRomb("romb2", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb2);

        Mesh* romb3 = object2D::CreateRomb("romb3", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb3);

        Mesh* romb4 = object2D::CreateRomb("romb4", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb4);

        Mesh* romb5 = object2D::CreateRomb("romb5", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb5);

        Mesh* romb6 = object2D::CreateRomb("romb6", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb6);

        Mesh* romb7 = object2D::CreateRomb("romb7", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb7);

        Mesh* romb8 = object2D::CreateRomb("romb8", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb8);

        Mesh* romb9 = object2D::CreateRomb("romb9", corner, lengthRomb, glm::vec3(1, 0, 0), true);
        AddMeshToList(romb9);
    }
}


void Tema1::FrameStart()
{
    glClearColor(0.3, 0.3, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    translateX_stea += deltaTimeSeconds * 100;
    translateX_hexaR -= deltaTimeSeconds * 100;
    angularStep -= deltaTimeSeconds;

    glm::ivec2 resolution = window->GetResolution();
    
    //tabla de joc
    {
        //primul rand
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move, move / 5);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        //al doilea
        modelMatrix *= transform2D::Translate(-2 * move, move);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        //al treilea
        modelMatrix *= transform2D::Translate(-2 * move, move);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(move, 0);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
    }

    //vietile
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(-move, -move);
        RenderMesh2D(meshes["squareHealth"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(-move, 0);
        RenderMesh2D(meshes["squareHealth"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(-move, 0);
        RenderMesh2D(meshes["squareHealth"], shaders["VertexColor"], modelMatrix);
    }

    //patratele pentru romburi + romburile
    {
        //primul
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(0.5 * move, -move);
            RenderMesh2D(meshes["squareRomb"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(0.5 * move + lengthRomb, -move + squareSide / 2);
            RenderMesh2D(meshes["rombR"], shaders["VertexColor"], modelMatrix);
        }

        //al doilea
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(2 * move, -move);
            RenderMesh2D(meshes["squareRomb"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(2 * move + lengthRomb, -move + squareSide / 2);

            //disparitia unui romb dupa un anumit eveniment (apasarea unui buton)
            if (rombDispare) {
                scaleX_romb -= 0.5 * deltaTimeSeconds;
                scaleY_romb -= 0.5 * deltaTimeSeconds;
                modelMatrix *= transform2D::Translate(lengthRomb, (float)resolution.y);
                modelMatrix *= transform2D::Scale(scaleX_romb, scaleY_romb);
                modelMatrix *= transform2D::Translate(-lengthRomb, (float)-resolution.y);
                if (scaleX_romb <= 0 || scaleY_romb <= 0) {
                    scaleX_romb = scaleY_romb = 0;
                }
            }
            RenderMesh2D(meshes["rombP"], shaders["VertexColor"], modelMatrix);
        }

        //al treailea
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(3.5 * move, -move);
            RenderMesh2D(meshes["squareRomb"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(3.5 * move + lengthRomb, -move + squareSide / 2);
            RenderMesh2D(meshes["rombA"], shaders["VertexColor"], modelMatrix);
        }

        //al patrulea
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(5 * move, -move);
            RenderMesh2D(meshes["squareRomb"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(5 * move + lengthRomb, -move + squareSide / 2);
            RenderMesh2D(meshes["rombM"], shaders["VertexColor"], modelMatrix);
        }
    }


    //stea care se roteste in sens orar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(move + squareSide/2, move / 5 + squareSide/2);
    modelMatrix *= transform2D::Translate(translateX_stea, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["stea"], shaders["VertexColor"], modelMatrix);


    //inamicii

    //un hexagon
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resolution.x + lengthHexa, move / 5 + squareSide / 2);

        translateX_hexaR -= deltaTimeSeconds * 50;
        scaleX_hexaR -= 0.1 * deltaTimeSeconds;
        scaleY_hexaR -= 0.1 * deltaTimeSeconds;

        if (translateX_hexaR > -resolution.x)
            modelMatrix *= transform2D::Translate(translateX_hexaR, 0);

        if (translateX_hexaR < (-resolution.x + lengthHexa)) {
            translateX_hexaR = 0;

            modelMatrix *= transform2D::Scale(scaleX_hexaR, scaleY_hexaR);

            if (scaleX_hexaR < 0 && scaleY_hexaR < 0) {
                scaleX_hexaR = scaleY_hexaR = 0;
            }
        }
        RenderMesh2D(meshes["hexaR"], shaders["VertexColor"], modelMatrix);
    }

    //al doilea hexagon
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((float)resolution.x / 2, move * 6 / 5 + squareSide / 2);

        if (hexaDispareP) {
            modelMatrix *= transform2D::Scale(scaleX_hexaP, scaleY_hexaP);
            scaleX_hexaP -= 0.5 * deltaTimeSeconds;
            scaleY_hexaP -= 0.5 * deltaTimeSeconds;

            if (scaleX_hexaP < 0 && scaleY_hexaP < 0) {
                scaleX_hexaP = scaleY_hexaP = 0;
            }
        }

        RenderMesh2D(meshes["hexaP"], shaders["VertexColor"], modelMatrix);
    }
    
    //pun romburi pe patratele
    switch (leftMouse) {
        case 1:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(move + lengthRomb, move / 5 + squareSide/2);
            RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);
        case 2:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(2*move + lengthRomb, move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);
        case 3:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(3*move + lengthRomb, move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);
        case 4:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(move + lengthRomb, 6 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);
        case 5:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(2*move + lengthRomb, 6 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb5"], shaders["VertexColor"], modelMatrix);
        case 6:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(3*move + lengthRomb, 6 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb6"], shaders["VertexColor"], modelMatrix);
        case 7:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(move + lengthRomb, 11 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb7"], shaders["VertexColor"], modelMatrix);
        case 8:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(2*move + lengthRomb, 11 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb8"], shaders["VertexColor"], modelMatrix);
        case 9:
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(3*move + lengthRomb, 11 * move / 5 + squareSide / 2);
            RenderMesh2D(meshes["romb9"], shaders["VertexColor"], modelMatrix);
    }

    //dreptunghiul pentru viata jucatorului
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move / 5, move / 5);
        modelMatrix *= transform2D::Scale(1, 5.5);
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_F) {
        rombDispare = true;
    }

    if (key == GLFW_KEY_G) {
        hexaDispareP = true;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    //pentru detectia patratelei in care pun rombul
    glm::ivec2 resolution = window->GetResolution();
    if ((float)mouseX > move && (float)mouseX < (move + squareSide)) {
        if (((float)mouseY > (move / 5)) && (float)mouseY < (move / 5 + move))
            leftMouse = 1;
        if (((float)mouseY > (move / 5 + move)) && (float)mouseY < (move / 5 + 2 * move))
            leftMouse = 4;
        if (((float)mouseY > (move / 5 + 2*move)) && (float)mouseY < (move / 5 + 3 * move))
            leftMouse = 7;
        if ((float)mouseY > (move / 5 + 3 * move))
            leftMouse = 0;
    }
    if ((float)mouseX > 2 * move && (float)mouseX < (2 * move + squareSide)) {
        if ((float)mouseY > move / 5 && (float)mouseY < (move / 5 + move))
            leftMouse = 2;
        if ((float)mouseY > (move / 5 + move) && (float)mouseY < (move / 5 + 2*move))
            leftMouse = 5;
        if ((float)mouseY > (move / 5 + 2 * move) && (float)mouseY < (move / 5 + 3*move))
            leftMouse = 8;
        if ((float)mouseY > (move / 5 + 3 * move))
            leftMouse = 0;
    }
    if ((float)mouseX > 3 * move && (float)mouseX < (3 * move + squareSide)) {
        if ((float)mouseY > move / 5 && (float) mouseY < (move/5 + move))
            leftMouse = 3;
        if ((float)mouseY > (move / 5 + move) && (float)mouseY < (move / 5 + 2*move))
            leftMouse = 6;
        if ((float)mouseY > (move / 5 + 2 * move) && (float)mouseY < (move / 5 + 3*move))
            leftMouse = 9;
        if ((float)mouseY > (move / 5 + 3 * move))
            leftMouse = 0;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
