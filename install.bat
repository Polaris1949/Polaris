@echo off
md "%1\polaris"
robocopy .\include "%1\polaris" /mir
pause
