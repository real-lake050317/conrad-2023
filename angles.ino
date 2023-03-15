int theta1(int x, int y, int z){
  return 90 - (int)(180.0*atanf((float)(y)/x)/pi); //range: [-pi/2, pi/2]
}

int theta2(int x, int y, int z){
  return 90 - (int)(180.0*acosf((float)(z)/sqrt(x*x+y*y+z*z))/pi); //range: [0,pi]
}
