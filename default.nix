let
  pkgs = import <nixpkgs> { };
in
pkgs.stdenv.mkDerivation {
  name = "zvm";
  src = ./.;

  nativeBuildInputs = with pkgs; [ gcc make ];

  installPhase = ''
    mkdir -p $out/bin
    cp zvm $out/bin/zvm
  '';
}
