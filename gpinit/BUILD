cc_library(
    name = "camera",
    hdrs = ["camera.h"],
    deps = [
        "//third-party/glad:glad",
        "@glm//:glm",
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "cone",
    hdrs = ["cone.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "cube",
    hdrs = ["cube.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "cylinder",
    hdrs = ["cylinder.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "dodecahedron",
    hdrs = ["dodecahedron.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "ellipsoid",
    hdrs = ["ellipsoid.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "flight",
    hdrs = ["flight.h"],
    deps = [
        "@glfw//:glfw",
        ":camera",
        ":shader",
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "gpinit",
    hdrs = ["gpinit.h"],
    deps = [
        "//third-party/glad:glad",
        "@glfw//:glfw",
        "@glm//:glm",
        ":shader",
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "icosahedron",
    hdrs = ["icosahedron.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "oct",
    hdrs = ["oct.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "shader",
    hdrs = ["shader.h"],
    deps = [
        "//third-party/glad:glad",
        "@glm//:glm",
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "shape",
    hdrs = ["shape.h"],
    deps = [
        "//third-party/glad:glad",
        "@glm//:glm",
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "tetra",
    hdrs = ["tetra.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "torus",
    hdrs = ["torus.h"],
    deps = [":shape"],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "world",
    hdrs = ["world.h"],
    deps = [
        "@glm//:glm",
        ":shape",
        ":shader",
        ":camera",
        ],
    visibility = ["//visibility:public"],
)