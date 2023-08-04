rule(mode.debug,mode.release)

target("4-RayTracing")
    add_files("*.cpp")
    set_kind("binary")
    