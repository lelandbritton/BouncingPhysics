Simple game with raylib. It initializes a window and allows you to spawn balls with a left mouse click. Balls collide with each other and bounce away.

## macOS

Install raylib with Homebrew, then build and run the game:

```sh
brew install raylib
make
./bouncing_physics
```

If raylib is installed somewhere else, provide its prefix explicitly:

```sh
make RAYLIB_PREFIX=/path/to/raylib
```

## Windows

The Makefile expects the raylib development package at `C:\raylib`. Run it from a MinGW or raylib development shell:

```sh
make
./bouncing_physics.exe
```