while (<>) {
     s/\(([^)]*)\)/\(\)/g;
    print;
}