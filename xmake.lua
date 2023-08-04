set_config("toolchain","clang-cl")
set_config("lsp","clangd")
set_allowedarchs("windows|x64")
add_rules("mode.debug", "mode.release")

set_languages("cxx20")
includes("**/xmake.lua")