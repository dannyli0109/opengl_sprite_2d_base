#include "ProgramManager.h"

bool ProgramManager::Init()
{

    //Initialise GLFW, make sure it works. Put an error message here if you like.
    if (!glfwInit())
        return false;

    //Set resolution here, and give your window a different title.
    window = glfwCreateWindow(1280, 720, "Test Bed", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate(); //Again, you can put a real error message here.
        return false;
    }

    //This tells GLFW that the window we created is the one we should render to.
    glfwMakeContextCurrent(window);


    //Tell GLAD to load all its OpenGL functions.
    if (!gladLoadGL())
        return false;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glViewport(0, 0, 1280, 720);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);

    resourceManager = ResourceManager::CreateInstance();
    LoadAnimationFrames("player_walking_s", 60);
    LoadAnimationFrames("player_walking_n", 60);
    LoadAnimationFrames("player_walking_e", 60);
    LoadAnimationFrames("player_idle_s", 60);
    LoadAnimationFrames("player_idle_n", 60);
    LoadAnimationFrames("player_idle_e", 60);

    camera = new Camera({ 0, 0 }, { 1280, 720 }, 256);

    shader = new ShaderProgram("Quad.vert", "Quad.frag");
    spriteRenderer = new SpriteRenderer(shader, camera, 512);

    {
        player = new Entity(new Transform({ 0, 0, 0 }, 0, { 1, 1 }));

        {
            player->AddComponent(new PlayerInputManager(window));
        }

        {
            Sprite playerSprite = {};
            playerSprite.texture = resourceManager->GetTexture(int(TextureKey::running_s_start));
            playerSprite.tint = { 1.0f, 1.0f, 1.0f, 1.0f };
            playerSprite.tiling = { 1.0f, 1.0f };
            playerSprite.flipped = false;
            player->AddComponent(new SpriteContainer(playerSprite));
        }

        {
            std::unordered_map<std::string, Animation> animations;
            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 1.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_s_start) + i));
                }
                animations["running_s"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 1.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_n_start) + i));
                }
                animations["running_n"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 1.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
                }
                animations["running_e"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 1.0f;
                animation.flipped = true;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
                }
                animations["running_w"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 3.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_s_start) + i));
                }
                animations["idle_s"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 3.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_n_start) + i));
                }
                animations["idle_n"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 3.0f;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
                }
                animations["idle_e"] = animation;
            }

            {
                Animation animation;
                animation.frameCount = 60;
                animation.duration = 3.0f;
                animation.flipped = true;
                for (int i = 0; i < animation.frameCount; i++)
                {
                    animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
                }
                animations["idle_w"] = animation;
            }

            player->AddComponent(new SpriteAnimation(animations, "idle_s"));
        }
    }

    time = glfwGetTime();
    return true;
}

void ProgramManager::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - time;
        time = currentTime;
        //Tell GLFW to check if anything is going on with input, etc.
        glfwPollEvents();

        //Clear the screen – eventually do rendering code here.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        player->Update(deltaTime);

        spriteRenderer->Begin(shader, camera);
        glm::mat4 spriteTransform = glm::mat4(1.0f);
        //spriteRenderer->AddSprite(spriteTransform, resourceManager->GetTexture(TextureKey::walk0), { 1, 1, 1, 1 }, { 1, 1 }, false);
        player->Draw(spriteRenderer);
        spriteRenderer->End();

        //RenderGUI();

        //Swapping the buffers – this means this frame is over.
        glfwSwapBuffers(window);
    }
}

void ProgramManager::Destroy()
{
    glfwTerminate();
    // Cleanup GUI related
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ProgramManager::RenderGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Make window dockable
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // begin imgui window
    ImGui::Begin("Imgui window");
    // draw ui element in between
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
}
