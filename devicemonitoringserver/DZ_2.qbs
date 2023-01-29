import qbs

CppApplication {
    /*files: [
        "multiply41.cpp",
        "multiply41.h",
    ]
    /*files: [
        "mirror.cpp",
        "mirror.h",
    ]
    /*files: [
        "ro3.cpp",
        "ro3.h",
    ]
    /*files: [
        "messageencoder.cpp",
        "messageencoder.h",
    ]*/
    /*files: [
        "BaseEncoderExecutor.h",
    ]*/

   /* files: [
        "MessageSerializer.h",
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
