int i=0;
void setup()
{
  size(600,600,P3D);
}
void draw()
{
  background(0);
  translate(width/2,height/2);
  fill(255,0,0);
  rotateY(radians(60));
  rotateX(radians(60));
  box(200);
  
}