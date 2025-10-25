{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Add your packages here
   glfw
    pkg-config
    clang
    bear
    lldb
  ];

  shellHook = ''
    echo "Welcome to the development shell!"
    alias r=./build/main
  '';
}
