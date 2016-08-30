@echo off
echo "Compiling .."
cl.exe -c -Zi -nologo -EHsc -I..\external_libraries\SDL2-2.0.4\include\ game.cpp ball.cpp paddle.cpp main.cpp vector2.cpp graphics.cpp input_handler.cpp
echo "Linking .."
link.exe /out:pong.exe /INCREMENTAL /nologo /DEBUG /PDB:"pong.pdb" /LIBPATH:"..\external_libraries\SDL2-2.0.4\lib\x86" game.obj ball.obj paddle.obj main.obj vector2.obj graphics.obj input_handler.obj
