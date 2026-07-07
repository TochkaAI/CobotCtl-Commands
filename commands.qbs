import qbs
import qbs.FileInfo
import QbsUtl

Product {
    name: "CobotCtl"
    targetName: "cobotctl"
    condition: true

    Properties {
        name: "Commands"
        targetName: "commands"
        condition: project.isCobotCtlProject === true
    }

    type: "staticlibrary"

    Depends { name: "cpp" }
    Depends { name: "PProto" }
    Depends { name: "Detection"; required: false }
    Depends { name: "RapidJson"; required: false }
    Depends { name: "SharedLib" }
    Depends { name: "Yaml" }
    Depends { name: "Qt"; submodules: ["core", "network"] }

    cpp.defines: project.cppDefines;
    cpp.cxxFlags: project.cxxFlags
    cpp.cxxLanguageVersion: project.cxxLanguageVersion

    cpp.includePaths: [".."]

    files: [
        "commands.cpp",
        "commands.h",
        "error.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [
            FileInfo.joinPaths(exportingProduct.sourceDirectory, ".."),
        ]
    }

} // Product

