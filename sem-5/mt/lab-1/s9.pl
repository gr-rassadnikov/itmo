while (<>) {
     s/\(([^)]*)\)/\(\)/g;
    print;
}
