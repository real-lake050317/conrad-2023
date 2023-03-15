int theta1(int x, int y, int z){
  //atanf range: [-pi/2, pi/2]
  if (y >= 0){
    return (int)(180.0*atanf((float)(y)/x)/pi);
  }
  else {
    return (int)(180.0*atanf((float)(y)/x)/pi) + 180;
  }
}

int theta2(int x, int y, int z){
  //acosf range: [0, pi]
  return (int)(180.0*acosf((float)(z)/sqrt(x*x+y*y+z*z))/pi);
}
