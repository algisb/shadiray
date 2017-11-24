1. pass parameter to the program to load a custom model eg. ./shadiray-demo "./myobject.obj", the parameter is a path to the obj file
2. main camera is controlled using W,A,S,D to translate and arrow keys to rotate
3. ray caster and the viecone are controlled using T,F,G,H to translate and I,J,K,L to rotate
4. number key 1 is used to cast rays on to the scene using "brute-force" algorithm
5. number key 2 is used to cast rays on to the scene using "MT97" algorithm
6. ray cast information and performance info is shown in the console after key 1 or key 2 is pressed

note: models with triangle cound over 1000 will require significant time to raycast(over 10 seconds on average machine), the program isn't multi threaded therefore it will be frozen while rays are computed.
