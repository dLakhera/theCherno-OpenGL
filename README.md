# Compilation instructions

- Firstly move into the directory ```/src``` using ```cd src``` 
- Type in the following command in the terminal to compile the source code
    ```g++ -std=c++17 -I ./vendor/stb_image/ ./vendor/stb_image/*.cpp *.cpp -lGLEW -lGLU -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -w```
- To run the application, ``` ./a.out ```

## Authored by Deepak Lakhera