# AnoPlib
Animlets are not Particles library

AnoPlib - **A**nimlets are **no**t **P**articles library - provides a library for rendering small and fast animated effects using openGL.

AnoPlib is written in C++, other ports may follow. It is available under the [BSD license](LICENSE).

Why have I started this? I needed some way for thin, fast handling of small openGL-animations. Think of showing radio propagation in a traffic simulation with several hundreds or thousands of vehicles. Would be pretty ugly to have code bloat here.

<!-- imgs begin -->
<img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_emergency1.png" width="30%"/> <img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_signal1.png" width="30%"/> <img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_starfield1.png" width="30%"/> <img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_tentacle1.png" width="30%"/> <img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_wave1.png" width="30%"/> <img src="https://github.com/dkrajzew/AnoPlib/blob/main/docs/images/anop_wireless1.png" width="30%"/>
<!-- imgs end -->


## Idea; less brief

There are several particles implementations. Particles are generated, fall or move, disappear after a while and are regenerated. All in all very nice. Though, what I needed, is something that controls a set of small animated objects; each animation may contain a movement, but this is not mandatory. Because a larger number of such animations shall be rendered, each animation should be rendered fast. The complete "system" must control animations.

And well, yes, because "animation" is somehow ambiguous, we name the child "animlet".

## Road Map

What I would like next - someday better to say - is to allow a rapid animlet prototyping. Basically nothing more than defining the initial position and the behaviour of animlets either via an own language or by embedding the thing into doris!!!. We'll see.

As I have what I need and future extensions would be just a hobby, you may try motivating me by writing a mail or spending some money.

## Installation

The library itself needs openGL, the example application additionally glut. Having both installed should be enough to compile on Linux, just type make in the folder you have extracted the library into.

On Windows, you either have to set the environment variable "GLUT" to the path your glut includes and libs are located in or to include these path in the project settings.
