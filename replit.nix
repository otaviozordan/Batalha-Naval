{ pkgs }: {
	deps = [
   pkgs.cataract-unstable
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}