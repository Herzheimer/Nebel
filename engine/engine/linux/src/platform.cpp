#include "platform.h"
#include "game.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>

namespace Nebel
{
    // TODO: implement GameController
    // https://gist.github.com/adituv/b72ce0d0ee31e6382ae7c2136a4f7bc8
    SDL_Joystick* gGameController = NULL;
    const int JOYSTICK_DEAD_ZONE = 8000;
    float xDir = 0;
    float yDir = 0;

    std::vector<char> read_file(const std::string &filename) // const char* &filemane);
    {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (file)
        {
            size_t file_size = (size_t)file.tellg();
            std::vector<char> file_buffer(file_size);
            file.seekg(0);
            file.read(file_buffer.data(), file_size);
            file.close();
            return file_buffer;
        }else{
            throw std::runtime_error("Failed to open file");
        }
    }
    void UpdateController()//SDL_Event event)
    {
        for (size_t i = 0; i < Input::controller.size(); i++)
        {
            switch (Input::controller[i].type)
            {
                case SWITCH_CONTROLLER:
                    if (SDL_JoystickGetButton(gGameController, 0)) {
                        Input::controller[i].buttons_down[CONTROLLER_Y] = true;
                        //std::cerr << "no idea what button 0 is. (switch: Y, xbox360: A)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_Y] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 1)) {
                        Input::controller[i].buttons_down[CONTROLLER_B] = true;
                        //std::cerr << "no idea what button 1 is. (switch: B, xbox360: B)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_B] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 2)) {
                        Input::controller[i].buttons_down[CONTROLLER_A] = true;
                        //std::cerr << "no idea what button 2 is. (switch: A, xbox360: X)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_A] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 3)) {
                        Input::controller[i].buttons_down[CONTROLLER_X] = true;
                        //std::cerr << "no idea what button 3 is. (switch: X, xbox360: Y)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_X] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 4)) {
                        Input::controller[i].buttons_down[CONTROLLER_L] = true;
                        //std::cerr << "no idea what button 4 is(switch: L, xbox360: LB)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_L] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 5)) {
                        Input::controller[i].buttons_down[CONTROLLER_R] = true;
                        //std::cerr << "no idea what button 5 is(switch: R, xbox360: RB)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_R] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 6)) {
                        Input::controller[i].buttons_down[CONTROLLER_ZL] = true;
                        //std::cerr << "no idea what button 6 is(switch: ZL, xbox360: BACK)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_ZL] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 7)) {
                        Input::controller[i].buttons_down[CONTROLLER_ZR] = true;
                        //std::cerr << "no idea what button 7 is(switch: ZR, xbox360: START)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_ZR] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 8)) {
                        Input::controller[i].buttons_down[CONTROLLER_MINUS] = true;
                        //std::cerr << "no idea what button 8 is(switch: -, xbox360: xbox-btn)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_MINUS] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 9)) {
                        Input::controller[i].buttons_down[CONTROLLER_PLUS] = true;
                        //std::cerr << "no idea what button 9 is(switch: +, xbox360: LeftJoyButton)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_PLUS] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 10)) {
                        Input::controller[i].buttons_down[CONTROLLER_LEFT_JOYSTICK] = true;
                        //std::cerr << "no idea what button 10 is(switch: LeftJoyButton, xbox360: RightJoyButton)" << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_LEFT_JOYSTICK] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 11)) {
                        Input::controller[i].buttons_down[CONTROLLER_RIGHT_JOYSTICK] = true;
                        //std::cerr << "no idea what button 11 is(switch: RightJoyButton, xbox360: " << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_RIGHT_JOYSTICK] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 12)) {
                        Input::controller[i].buttons_down[CONTROLLER_HOME] = true;
                        //std::cerr << "no idea what button 12 is(switch: Home, xbox360: " << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_HOME] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 13)) {
                        Input::controller[i].buttons_down[CONTROLLER_CIRCLE_IN_SQUARE] = true;
                        //std::cerr << "no idea what button 13 is(switch: SquaredCircle, xbox360: " << std::endl;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_CIRCLE_IN_SQUARE] = false;
                    }
                    break;
                case XBOX_360_CONTROLLER:
                    if (SDL_JoystickGetButton(gGameController, 0)) {
                        Input::controller[i].buttons_down[CONTROLLER_A] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_A] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 1)) {
                        Input::controller[i].buttons_down[CONTROLLER_B] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_B] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 2)) {
                        Input::controller[i].buttons_down[CONTROLLER_X] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_X] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 3)) {
                        Input::controller[i].buttons_down[CONTROLLER_Y] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_Y] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 4)) {
                        Input::controller[i].buttons_down[CONTROLLER_LB] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_LB] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 5)) {
                        Input::controller[i].buttons_down[CONTROLLER_RB] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_RB] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 6)) {
                        Input::controller[i].buttons_down[CONTROLLER_BACK] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_BACK] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 7)) {
                        Input::controller[i].buttons_down[CONTROLLER_START] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_START] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 8)) {
                        Input::controller[i].buttons_down[CONTROLLER_XBOX] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_XBOX] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 9)) {
                        Input::controller[i].buttons_down[CONTROLLER_LEFT_JOYSTICK] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_LEFT_JOYSTICK] = false;
                    }
                    if (SDL_JoystickGetButton(gGameController, 10)) {
                        Input::controller[i].buttons_down[CONTROLLER_RIGHT_JOYSTICK] = true;
                    }else{
                        Input::controller[i].buttons_down[CONTROLLER_RIGHT_JOYSTICK] = false;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }
    void InitController()
    {
        size_t num_controller = SDL_NumJoysticks();
        if (num_controller > 0)
        {
            Input::controller.resize(num_controller);
            for (size_t i = 0; i < num_controller; i++)
            {
                Controller controller;
                switch (SDL_GameControllerTypeForIndex(i))
                {
                    case SDL_CONTROLLER_TYPE_XBOX360:
                        controller.type = XBOX_360_CONTROLLER;
                        break;
                    case SDL_CONTROLLER_TYPE_XBOXONE:
                        controller.type = XBOX_ONE_CONTROLLER;
                        break;
                    case SDL_CONTROLLER_TYPE_PS3:
                        controller.type = PS3_CONTROLLER;
                        break;
                    case SDL_CONTROLLER_TYPE_PS4:
                        controller.type = PS4_CONTROLLER;
                        break;
                    case SDL_CONTROLLER_TYPE_PS5:
                        controller.type = PS5_CONTROLLER;
                        break;
                    case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO:
                        controller.type = SWITCH_CONTROLLER;
                        break;
                    // case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT:
                    //     std::cout << "Controller type: Nintendo Switch JoyCon_Left" << std::endl;
                    //     break;
                    // case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT:
                    //     std::cout << "Controller type: Nintendo Switch JoyCon_Right" << std::endl;
                    //     break;
                    // case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_PAIR:
                    //     std::cout << "Controller type: Nintendo Switch JoyCon_Pair" << std::endl;
                    //     break;
                    default:
                        std::cout << "Controller type not found!" << std::endl;
                        controller.type = UNKNOWN_CONTROLLER;
                        break;
                }
                controller.resetButtons();
                controller.gGameController = SDL_JoystickOpen(i);
                if (controller.gGameController == nullptr) {
                    printf("Warning: unable to open game controller %d!  SDL Error: %s\n", i, SDL_GetError());
                }else{
                    //Input::controller[i] = controller;
                }
                Input::controller[i] = controller;
            }
        } else{
            std::cout << "No Controller" << std::endl;
        }
    }
    void Platform::InitInput()
    {
        InitController();
    }
    void Platform::UpdateInput()
    {
        Input::last_MousePosition = Input::MousePosition;
        Input::mouse_buttons_last_down[LMB] = Input::mouse_buttons_down[LMB];
        Input::mouse_buttons_last_down[MMB] = Input::mouse_buttons_down[MMB];
        Input::mouse_buttons_last_down[RMB] = Input::mouse_buttons_down[RMB];
        Input::mouse_buttons_down[LMB] = false;
        Input::mouse_buttons_down[MMB] = false;
        Input::mouse_buttons_down[RMB] = false;
        Input::ResetKeys();

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[ SDL_SCANCODE_W ])
        {
            Input::keys_down[W] = true;
        }
        if(keystates[ SDL_SCANCODE_A ])
        {
            Input::keys_down[A] = true;
        }
        if(keystates[ SDL_SCANCODE_S ])
        {
            Input::keys_down[S] = true;
        }
        if(keystates[ SDL_SCANCODE_D ])
        {
            Input::keys_down[D] = true;
        }
        if(keystates[ SDL_SCANCODE_E ])
        {
            Input::keys_down[E] = true;
        }
        if(keystates[ SDL_SCANCODE_F ])
        {
            Input::keys_down[F] = true;
        }
        if(keystates[ SDL_SCANCODE_Q ])
        {
            Input::keys_down[Q] = true;
        }
        if(keystates[ SDL_SCANCODE_UP ])
        {
            Input::keys_down[Up] = true;
        }
        if(keystates[ SDL_SCANCODE_DOWN ])
        {
            Input::keys_down[Down] = true;
        }
        if(keystates[ SDL_SCANCODE_LEFT ])
        {
            Input::keys_down[Left] = true;
        }
        if(keystates[ SDL_SCANCODE_RIGHT ])
        {
            Input::keys_down[Right] = true;
        }
        if(keystates[ SDL_SCANCODE_LSHIFT ])
        {
            Input::keys_down[Shift] = true;
            Input::keys_down[LShift] = true;
        }
        if(keystates[ SDL_SCANCODE_RSHIFT ])
        {
            Input::keys_down[Shift] = true;
            Input::keys_down[RShift] = true;
        }
        if(keystates[ SDL_SCANCODE_ESCAPE ])
        {
            Input::keys_down[Esc] = true;
        }
        if(keystates[ SDL_SCANCODE_SPACE ])
        {
            Input::keys_down[Space] = true;
        }
        UpdateController(); //event);
    }
    void Platform::Create(uint32_t w, uint32_t h, const char* t)
    {
        width = w;
        height = h;
        title = t;
        
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(
            SDL_WINDOW_OPENGL
            //SDL_WINDOW_VULKAN
            | SDL_WINDOW_SHOWN
            | SDL_WINDOW_RESIZABLE
            | SDL_WINDOW_ALLOW_HIGHDPI
            );
        window = SDL_CreateWindow(t,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, 
                w,
                h,
                window_flags//SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                );

        SDL_SetWindowMinimumSize(window, 500, 350);
        //SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
        //SDL_SetRelativeMouseMode(SDL_TRUE);

        // OpenGL setup the graphics context
        context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Setup our function pointers
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        glViewport(0,0,width, height);

        Input::Init();
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        screen_width = DM.w;
        screen_height = DM.h;
        int wi = 0;
        int he = 0;
        SDL_GL_GetDrawableSize(window, &wi, &he);
        virtual_width = wi;
        virtual_height = he;
        // TODO: get all displays plus active display!!
        SDL_GetDisplayDPI(0, &diagonal_dpi, &horizontal_dpi, &vertical_dpi);
        InitInput();
    }

    void Platform::Prepare()
    {
        //
    }

    void Platform::Update()
    {
        UpdateInput();
        SDL_GetMouseState(&Input::MousePositionI.x, &Input::MousePositionI.y);
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                should_close = true;
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                //std::cout << "mouse has been moved\n";
                Input::MousePosition = {event.motion.x, event.motion.y};
                //Input::MouseDelta = {event.motion.xrel, event.motion.yrel};
            }
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    updateWidthAndHeight();
                    std::cout << "resized!" << std::endl;
                }
            }
            
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                switch (event.button.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        switch (event.button.button)
                        {
                        case SDL_BUTTON_LEFT:
                            Input::mouse_buttons_down[LMB] = true;
                            break;
                        case SDL_BUTTON_MIDDLE:
                            Input::mouse_buttons_down[MMB] = true;
                            break;
                        case SDL_BUTTON_RIGHT:
                            Input::mouse_buttons_down[RMB] = true;
                            break;
                        }
                        break;
                }
            }
            //std::cout << "screen_width: " << screen_width << std::endl;
            //std::cout << "screen_height: " << screen_height << std::endl;
            //std::cout << "virtual width: " << virtual_width << std::endl;
            //std::cout << "virtual height: " << virtual_height << std::endl;
            //std::cout << "ddpi: " << diagonal_dpi << std::endl;
            //std::cout << "hdpi: " << horizontal_dpi << std::endl;
            //std::cout << "vdpi: " << vertical_dpi << std::endl;
        }
        Input::MouseDelta.x = Input::MousePosition.x - Input::last_MousePosition.x;
        Input::MouseDelta.y = Input::last_MousePosition.y - Input::MousePosition.y;

        if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            gGameController = SDL_JoystickOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
            if(event.type == SDL_JOYAXISMOTION )
            {
                //Motion on controller 0
                if(event.jaxis.which == 0 )
                {
                    //X axis motion
                    if(event.jaxis.axis == 0 )
                    {
                        //Left of dead zone
                        if(event.jaxis.value < -JOYSTICK_DEAD_ZONE )
                        {
                            xDir = -1;
                        }
                        //Right of dead zone
                        else if(event.jaxis.value > JOYSTICK_DEAD_ZONE )
                        {
                            xDir =  1;
                        }
                        else
                        {
                            xDir = 0;
                        }
                    }else if(event.jaxis.axis == 1 )
                    {
                        //Below of dead zone
                        if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
                        {
                            yDir = -1;
                        }
                        //Above of dead zone
                        else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
                        {
                            yDir =  1;
                        }
                        else
                        {
                            yDir = 0;
                        }
                    }
                }
            }
        }
    }

    void Platform::LateUpdate()
    {
        SDL_GL_SwapWindow(window);
    }

    bool Platform::ShouldClose()
    {
        return should_close;
    }

    double Platform::GetTime()
    {
        return SDL_GetPerformanceCounter();
    }

    void Platform::updateWidthAndHeight()
    {
        // SDL_DisplayMode DM;
        // SDL_GetCurrentDisplayMode(0, &DM);
        // screen_width = DM.w;
        // screen_height = DM.h;
        int w = 0;
        int h = 0;
        SDL_GetWindowSize(window, &w, &h);
        width=w;
        height=h;
        //SDL_GL_GetDrawableSize(window, &w, &h); // canvas size
        SDL_GetDisplayDPI(0, &diagonal_dpi, &horizontal_dpi, &vertical_dpi);
        virtual_width = w;
        virtual_height = h;
        // TODO: get all displays plus active display!!
        Game::renderer->Resize();
        Game::camera2d->update();
    }

    void Platform::setfullscreen(bool on)
    {
        if (on)
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }else{
            SDL_SetWindowFullscreen(window, 0);
        }
    }

    Platform::~Platform()
    {
        Input::Terminate();
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    //void Platform::GetInstanceExtensions(uint32_t &instanceExtensionCount, const char** instanceExtensions)
    //{
	//    SDL_Vulkan_GetInstanceExtensions(window, &instanceExtensionCount, instanceExtensions);
    //}
    //void Platform::CreateSurface(VkInstance &instance, VkSurfaceKHR* surface)
    //{
    //    SDL_Vulkan_CreateSurface(window, instance, surface);
    //}
}