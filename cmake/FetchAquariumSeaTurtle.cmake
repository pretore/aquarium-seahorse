include(FetchContent)

FetchContent_Declare(
        aquarium-sea-turtle
        GIT_REPOSITORY https://github.com/pretore/aquarium-sea-turtle.git
        GIT_TAG v3.0.0
        GIT_SHALLOW 1
)

FetchContent_MakeAvailable(aquarium-sea-turtle)
