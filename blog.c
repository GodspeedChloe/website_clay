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

    Clay_Sizing layoutExpand = {
        .width = CLAY_SIZING_GROW(),
        .height = CLAY_SIZING_GROW()
    };

    Clay_Color almostBlack = {12, 15, 10, 255};
    Clay_Color brightYellow = {251,255,18,255};
    Clay_Color pinkRed = {255, 32, 110, 255};
    Clay_Color brightAqua = {65, 234, 212, 255};
    Clay_Color electricBlue = {0, 46, 255, 255};
    Clay_Color white = {255, 255, 255, 255};

    while (!WindowShouldClose()){
        // Run Once per Frame
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        Clay_BeginLayout();

        // Build UI here
        CLAY(
            CLAY_ID("OuterContainer"),
            CLAY_RECTANGLE({ .color = almostBlack}),
            CLAY_LAYOUT({
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = layoutExpand,
                .padding = {16, 16}
            })
        ) {
            CLAY(
                CLAY_ID("HeaderBar"),
                CLAY_RECTANGLE({ 
                    .color = brightYellow,
                    .cornerRadius = 8
                }),
                CLAY_LAYOUT({
                    .sizing = {
                        .height = CLAY_SIZING_FIXED(60),
                        .width = CLAY_SIZING_GROW()
                    }
                })
            ){}
            CLAY(
                CLAY_ID("LowerContent"),
                CLAY_LAYOUT({
                    .sizing = layoutExpand,
                    .padding = (16, 16)
                })
            ){
                CLAY(
                    CLAY_ID("Sidebar"),
                    CLAY_LAYOUT({
                        .sizing = {
                            .width = CLAY_SIZING_FIXED(250),
                            .height = CLAY_SIZING_GROW()
                        }
                    }),
                    CLAY_RECTANGLE({
                        .color = brightAqua,
                        .cornerRadius = 8
                    })
                ){}
                CLAY(
                    CLAY_ID("MainContentContainer"),
                    CLAY_LAYOUT({
                        .sizing = layoutExpand,
                        .padding = {8, 8}
                    }),
                    CLAY_RECTANGLE({
                        .color = pinkRed,
                        .cornerRadius = 8
                    })
                ){
                    CLAY(
                        CLAY_ID("MainContent"),
                        CLAY_LAYOUT({
                            .sizing = layoutExpand
                        }),
                        CLAY_RECTANGLE({
                            .color = white,
                            .cornerRadius = 8
                        })
                    ){}
                }
            }
        }


        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands);
        EndDrawing();
    }
}
