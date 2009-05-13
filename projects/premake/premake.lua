addoption( "GUCEF_HOME", "Specify the location of the GUCEF archive" )
addoption( "GUCE_HOME", "Specify the location of the GUCE archive" )

dofile("functions.lua")

project_setup("GU")

--[[---------------------------------------------------------------------------]]
--[[                                                                           ]]
--[[    Add packages from other projects                                       ]]
--[[                                                                           ]]
--[[---------------------------------------------------------------------------]]

-- THIS IS NOT WORKING
--add_packages_from_file_option( "GUCEF_HOME" )
--add_packages_from_file_option( "GUCE_HOME" )

--[[---------------------------------------------------------------------------]]
--[[                                                                           ]]
--[[    Add packages                                                           ]]
--[[                                                                           ]]
--[[---------------------------------------------------------------------------]]


add_package("guCORE")
add_package_dependency("gucefMT")

add_package("guMG_TicTacToe")
add_package_dependency("guCORE")

add_application("gu")
add_package_dependency("guCORE")

