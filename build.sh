cd build

rm -rf ./*

cd ..

mkdir -p build/site                                                       \
&& clang                                                                  \
-Wall                                                                     \
-Werror                                                                   \
-Os                                                                       \
-DCLAY_WASM                                                               \
-mbulk-memory                                                             \
--target=wasm32                                                           \
-nostdlib                                                                 \
-Wl,--strip-all                                                           \
-Wl,--export-dynamic                                                      \
-Wl,--no-entry                                                            \
-Wl,--export=__heap_base                                                  \
-Wl,--initial-memory=6553600                                              \
-o build/site/index.wasm  						                          \
-v \
blog.c                                                                    \
blogcontent.c                                                             \
&& cp index.html build/site/index.html && cp -r fonts/ build/site/fonts   \
&& cp index.html build/site/index.html && cp -r images/ build/site/images
