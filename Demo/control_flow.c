

#ifndef sizeTYPE
#define sizeTYPE float
#endif

enum e_shape {
  CYLINDER,
  CONE,
  BOX,
};

#define PI 3.14159265

extern int validShape ( enum e_shape shape, sizeTYPE x, sizeTYPE y, sizeTYPE z );

sizeTYPE widthX =0;
sizeTYPE lengthY =0;
sizeTYPE heightZ =0;


void setDimensions (sizeTYPE x, sizeTYPE y, sizeTYPE z) {

    widthX = x;
    lengthY = y;
    heightZ = z;	
}


sizeTYPE computeBaseArea ( enum e_shape shape ) {
    sizeTYPE area, radius;

    if (!validShape( shape, widthX, lengthY, heightZ ))
    {
        area = 0;
    }
    else
    {
        switch (shape) {
          case BOX:      area = widthX * lengthY; break;
          case CONE:     radius = widthX/2;  area = PI *(radius * radius); break;
          case CYLINDER: radius = widthX/2;  area = PI *(radius * radius); break;
        }
    }

    return area;
}


sizeTYPE computeVolume ( enum e_shape shape ) {
    sizeTYPE volume, radius;

    if (!validShape( shape, widthX, lengthY, heightZ ))
    {
        volume = 0;
    }
    else
    {
        switch (shape) {
          case BOX:      volume = widthX * lengthY * heightZ; break;
          case CONE:     radius = widthX/2;  volume = (1/3)*heightZ * (PI *(radius * radius)); break;
          case CYLINDER: radius = widthX/2;  volume = heightZ * (PI *(radius * radius)); break;
        }
       volume = widthX * lengthY * heightZ;
    }
    return volume;
}


int Status;


void partitionExample ( 
     unsigned char numberOfIterations) {
     
    if (numberOfIterations < 20)
        Status =  1;
    else if (numberOfIterations < 40)
        Status =  2;
    else if (numberOfIterations < 60)
        Status =  3;
    else if (numberOfIterations < 80)
        Status =  4;
    else if (numberOfIterations < 100)
        Status =  5;    
        
}


void someExternalFunctionA ();
void someExternalFunctionB();
void someExternalFunctionC();
void someExternalFunctionD();
void someExternalFunctionE();

void controlFlowExample () {
    
      someExternalFunctionA();
      someExternalFunctionB();
      someExternalFunctionC();
      someExternalFunctionD();
      someExternalFunctionE();
    }
    

    
    
    
    