******************************************************************
Postprocessing Shaders by Nils Daumann (nils_daumann@online.de)
******************************************************************
Version: 0.05

******************************************************************
Thanks
******************************************************************
I want to thank everyone who answers to my sometimes very stupid
beginner questions.


******************************************************************
Overview
******************************************************************
I want to provide a collection of postprocessing shaders
supporting both, OpenGL and DirectX. They are all written to be
used together with my PostProcessing class.

Please tell me what kind of postprocessing shaders you need!


******************************************************************
How to use the effects
******************************************************************
The complexity of the different effects is very different.
Some will need a cuple of parameters and more then one textures.
Many are done through chaining different shaders. In such a case
the shader files are numbered in the order they have to be used.
GL or DX in the shaders filenames are showing if it is a GLSL
or a HLSL Shader.
For more informations on how to use the shaders, please look
at the examples.


******************************************************************
Version 0.05
******************************************************************
- Invert Colors (PS 1.4)
- Bloom (4 Shaders, the first needs PS 1.4 the others PS 2.0)


******************************************************************
License
******************************************************************
Copyright (c) 2008 Nils Daumann
 
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:
 
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.