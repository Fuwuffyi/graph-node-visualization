with import <nixpkgs> { config.allowUnfree = true; };
clangStdenv.mkDerivation {

  name = "test-g++-shell";
  nativeBuildInputs = [
    pkgs.clang-tools
    pkgs.clang
    pkgs.gcc
    pkgs.gdb
    pkgs.cmake
    pkgs.gnumake
    pkgs.lunarvim
    pkgs.valgrind
    pkgs.pkg-config
  ];

  buildInputs = with pkgs; [
    pkgs.glm
    pkgs.SDL2
    pkgs.SDL2_ttf
  ];
}
