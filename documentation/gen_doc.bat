set TEST_MAKER_DOT_DIR=C:\Program Files (x86)\Graphviz2.38\bin




set TEST_MAKER_DOC_DIR=%~dp0
echo %TEST_MAKER_DOC_DIR:~0,-1
set TEST_MAKER_WORKSPACE=%TEST_MAKER_DOC_DIR%..
rmdir -rf %TEST_MAKER_DOC_DIR%html
%TEST_MAKER_DOC_DIR%doxygen.exe %TEST_MAKER_DOC_DIR%doxygen_configuration.cfg