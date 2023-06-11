class pool {
 public:
  void build();          // 初始数据
  double rail_length();  // 围栏长度
  double rail_area();    // 围栏面积

 private:
  double cir_area(double);
  double radius;  // 半径
  double c;       // 走道宽
};