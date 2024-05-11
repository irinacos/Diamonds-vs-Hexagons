#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        glm::vec3 corner, cornerUpRight, cornerUpLeft, middleOfScreen, offScreen;
        float translateX_hexaR, translateX_hexaP, translateX_hexaA, translateX_hexaM, translateX_stea;
        float scaleX_romb, scaleY_romb, scaleX_hexaR, scaleY_hexaR, scaleX_hexaP, scaleY_hexaP;
        float move, squareSide, lengthRomb, lengthHexa, lengthStea;
        float angularStep;
        bool rombDispare, hexaDispareR, hexaDispareP;
        int leftMouse;
    };
}   // namespace m1
