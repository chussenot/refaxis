project('utils', 'cpp', default_options: ['cpp_std=c++17'])

# Find and use the nlohmann_json package
nlohmann_json = dependency('nlohmann_json', version : '3.11.2')
cpptoml = dependency('cpptoml', version: '0.1.1')
cxxopts = dependency('cxxopts', '2.2.1')
hiredis = dependency('hiredis', '1.1.0')

# Define the 'bin' directory
bin_dir = 'bin'

executable('refaxis', ['src/refaxis.cpp', 'src/utils/env_utils.cpp'],
           dependencies: [nlohmann_json, cpptoml, cxxopts, hiredis])