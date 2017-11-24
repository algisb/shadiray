1. pass a parameter to the program to load a custom model eg. ./shadiray-demo "./myobject.obj"(the parameter is a path to the obj file)
2. main camera is controlled using W,A,S,D to translate and arrow keys to rotate
3. ray caster and the viewcone are controlled using T,F,G,H to translate and I,J,K,L to rotate
4. number key 1 is used to cast cone of rays on to the scene using "brute-force" algorithm
5. number key 2 is used to cast cone of rays rays on to the scene using "MT97" algorithm
7. number key 3 is used to cast ray box volume on to the scene using "brute-force" algorithm
8. number key 4 is used to cast ray box volume on to the scene using "MT97" algorithm
9. ray cast information and performance info is shown in the console after performing a raycast
10. contatct points are marked with red axis and stored in a log file
11. models can be scaled using +/- buttons

note: models with triangle count over 1000 will require significant time to raycast(over 10 seconds on average machine), the program isn't multi threaded therefore it will be frozen while intersections are computed.
