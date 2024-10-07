@echo off
echo "Compiling .."
cl.exe -c -Zi -nologo -EHsc -I..\external_libraries\SDL2-2.0.4\include\ Game.cpp Table.cpp Ball.cpp Paddle.cpp Vector2.cpp Graphics.cpp InputHandler.cpp Scoreboard.cpp
echo "Linking .."
link.exe /out:pong.exe /INCREMENTAL /nologo /SUBSYSTEM:CONSOLE /DEBUG /PDB:"pong.pdb" /LIBPATH:"..\external_libraries\SDL2-2.0.4\lib\x64" Ball.obj Paddle.obj Table.obj Vector2.obj Graphics.obj InputHandler.obj Scoreboard.obj Game.obj 
