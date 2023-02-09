import qbs

CppApplication {
    /*files: [
        "commandcenter.cpp",
        "commandcenter.h",
    ]*/
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: product.sourceDirectory

    Group {
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Group {
        name: "C++"
        prefix: "**/"
        files: [
            "*.h","*.cpp"
        ]
    }
}
