#ifndef JOINT_H
#define JOINT_H

class Naub;

class Joint {
 public:
	Joint(Naub *a, Naub * b);
	Naub *a;
	Naub *b;
};

#endif
