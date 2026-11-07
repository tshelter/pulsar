{
  description = "PULSAR - Multi-protocol Internet Connectivity Observatory";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      formatter.${system} = pkgs.nixfmt-tree;

      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "pulsar";
        version = "0.0.3";

        src = ./.;

        nativeBuildInputs = [
          pkgs.gcc
          pkgs.gnumake
        ];

        dontFixup = true;

        buildPhase = ''
          make -C src
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp src/pulsar $out/bin/pulsar
        '';
      };

      devShells.${system}.default = pkgs.mkShell {
        buildInputs = [
          pkgs.gcc
          pkgs.gnumake
          pkgs.git
          pkgs.openssh
          pkgs.curl
          pkgs.jq
          pkgs.nixpkgs-fmt
        ];

        shellHook = ''
          export NIXFLAKES_HELP="PULSAR dev shell"
          echo "PULSAR dev shell ready"
        '';
      };
    };
}
