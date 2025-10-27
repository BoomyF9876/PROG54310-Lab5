#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Unable");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));

    camera = new Camera(
        WindowController::GetInstance().GetResolution(),
        { 200, 200, 200 }, { 0, 0, 0 }, { 0, 1, 0 }
    );
}

void GameController::RunGame()
{
    shaderColor = new Shader();
    shaderColor->LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = new Shader();
    shaderDiffuse->LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    meshLight = new Mesh();
    meshLight->Create(shaderColor);
    meshLight->SetPosition({ 100, 50, 0 });
    meshLight->SetScale({ 0.1f, 0.1f, 0.1f });

    for (int i = 0; i < 10; i++)
    {
        Mesh* mesh = new Mesh();
        mesh->Create(shaderDiffuse);
        mesh->SetLightColor({ 1.0f, 1.0f, 1.0f });
        mesh->SetLightPosition(meshLight->GetPosition());
        mesh->SetCameraPosition(camera->GetPosition());
        mesh->SetScale({ 0.15f, 0.15f, 0.15f });
        mesh->SetPosition({glm::linearRand(-100.0f, 100.0f), glm::linearRand(-100.0f, 100.0f) , glm::linearRand(-100.0f, 100.0f) });
        meshes.push_back(mesh);
    }

    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    do {
        //mesh->MoveTexture(-0.0001f, -0.0001f);

        //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //{
        //    mesh->MoveTexture(0, -0.01f);
        //}
        //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //{
        //    mesh->MoveTexture(0.01f, 0);
        //}
        //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //{
        //    mesh->MoveTexture(0, 0.01f);
        //}
        //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //{
        //    mesh->MoveTexture(-0.01f, 0);
        //}

        //System::Windows::Forms::Application::DoEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        meshLight->Render(camera->GetProjection() * camera->GetView());
        
        for (auto& mesh : meshes)
        {
            mesh->SetRotation(mesh->GetRotation() + glm::vec3(0.0f, 0.001f, 0.0f));
            mesh->Render(camera->GetProjection() * camera->GetView());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0
    );

    for (auto& mesh : meshes)
    {
        delete mesh;
    }
    delete meshLight;
    delete shaderColor;
    delete shaderDiffuse;
    delete camera;
}
