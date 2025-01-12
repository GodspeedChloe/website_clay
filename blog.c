#define CLAY_IMPLEMENTATION
#include "./clay-0.12/clay.h"
#include "./clay-0.12/renderers/raylib/clay_renderer_raylib.c"

int main(void){
    Clay_Raylib_Initialize(FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena){
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory
    };
    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    });

    while (!WindowShouldClose()){
        // Run Once per Frame

        Clay_BeginLayout();

        // Build UI here
        CLAY(
            CLAY_RECTANGLE({ .color = {255, 0, 0, 255}}),
            CLAY_LAYOUT({
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW()
                }
            })
        ) {}


        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands);
        EndDrawing();
    }
}
