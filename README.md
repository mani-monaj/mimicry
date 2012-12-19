mimicry (copycat) 
=======

This is the code for [this little competetion](http://www.meetup.com/VanDev/events/93217772/). Short presentation can be found [here](http://goo.gl/ZHrVP).

### How to build

You need a descent `C++` compiler and `cmake` to compile this code.

```bash
git clone https://github.com/mani-monaj/mimicry
cd mimicry
mkdir build && cd build
cmake ..
make
```

The executable will be placed in `build/bin`.

### Disclaimer

It turned out during the meetup that the original problem is called [copycat](http://en.wikipedia.org/wiki/Copycat_(software)). This code is by no means a formal way to solve the copycat problem. It is a heuristic approach to solve a subset of copycat problems. Please check [here](http://en.wikipedia.org/wiki/Copycat_(software)#External_links) for some formal descriptions and solutions.

### Sample Output

```bash
./mimicry abc abbddd xyz
1,xyyaaa,[Rule 0: At Pose 1 : Change scale from 1 to 2][Rule 1: At Pose 2 : Increment by 1 Change scale from 1 to 3],76
2,xyyddd,[Rule 0: At Pose 1 : Change scale from 1 to 2][Rule 1: At Pose 2 : Replace with d Change scale from 1 to 3],100

./mimicry abbc abc asdd
1,asdd,[Rule 0: At Pose 1 : Change scale from 2 to 1],25
2,asdd,[Rule 0: At Pose 1 : Change scale from 2 to 1],25
3,asd,[Rule 0: At any pose change scale from 2 to 1],25
4,asd,[Rule 0: At any pose change scale from 2 to 1],25
```
