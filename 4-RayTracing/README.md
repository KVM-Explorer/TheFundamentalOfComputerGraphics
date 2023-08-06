
## 坐标系

 右手系，X向右，Y向上。光线和图像生成阶段，按照从图像左上角到右下角的顺序遍历。因而在第一步时需要进行坐标的映射，使左上角的像素映射到空间的左上角，然后以图像中心建立图像坐标系。

## 线性表示

### 基向量表示

使用三角形的顶点v0作为三角形平面原点，v1-0 和 v2-v0分别作为基向量，使用α(v1-v0) + β(v2-v0)表示三角形内部顶点。当满足约束条件 alpha + beta <=1 且 alpha，beta>=0时，在三角形内部存在交点

对过程构建线性方程组并使用克莱姆法则进行求解，其过程如下
```cpp
    float detM = (v0.x - v1.x) * (v0.y - v2.y) * r.direction.z +
                 (v0.y - v1.y) * (v0.z - v2.z) * r.direction.x +
                 (v0.z - v1.z) * (v0.x - v2.x) * r.direction.y -
                 (v0.z - v1.z) * (v0.y - v2.y) * r.direction.x -
                 (v0.y - v1.y) * (v0.x - v2.x) * r.direction.z -
                 (v0.x - v1.x) * (v0.z - v2.z) * r.direction.y;

    float detA = (v0.x - v2.x) * (v0.z - r.origin.z) * r.direction.y +
                 (v0.y - v2.y) * (v0.x - r.origin.x) * r.direction.z +
                 (v0.z - v2.z) * (v0.y - r.origin.y) * r.direction.x -
                 (v0.z - v2.z) * (v0.x - r.origin.x) * r.direction.y -
                 (v0.y - v2.y) * (v0.z - r.origin.z) * r.direction.x -
                 (v0.x - v2.x) * (v0.y - r.origin.y) * r.direction.z;

    float detB = (v0.x - v1.x) * (v0.y - r.origin.y) * r.direction.z +
                 (v0.y - v1.y) * (v0.z - r.origin.z) * r.direction.x +
                 (v0.z - v1.z) * (v0.x - r.origin.x) * r.direction.y -
                 (v0.z - v1.z) * (v0.y - r.origin.y) * r.direction.x -
                 (v0.y - v1.y) * (v0.x - r.origin.x) * r.direction.z -
                 (v0.x - v1.x) * (v0.z - r.origin.z) * r.direction.y;

    float detC = (v0.x - v1.x) * (v0.y - v2.y) * (v0.z - r.origin.z) +
                 (v0.y - v1.y) * (v0.z - v2.z) * (v0.x - r.origin.x) +
                 (v0.z - v1.z) * (v0.x - v2.x) * (v0.y - r.origin.y) -
                 (v0.z - v1.z) * (v0.y - v2.y) * (v0.x - r.origin.x) -
                 (v0.y - v1.y) * (v0.x - v2.x) * (v0.z - r.origin.z) -
                 (v0.x - v1.x) * (v0.z - v2.z) * (v0.y - r.origin.y);

    float alpha = detA / detM;
    float beta = detB / detM;
    float t = detC / detM;

```

## 材质

不同的高光衰减项`p`对于材质高光区域的聚集程度起着决定性的作用，材质是否考虑单独添加`p`

## 光源

**Problem0**
对于点光源而言，其存在辐射度随半径衰减的物理规律，但是在实际操作中采取如下方式位置+光强定义点光源，实际测试中发现非常难以调试并且光强衰减过于迅速导致一片黑，考虑可能在光源的定义方面理解存在缺陷 **TODO**
```cpp
    PointLight light0{{1, 1, -2}, {0.9, 0.9, 0.9}};
```

## 阴影

目前阴影直接采用叠加环境光照进行处理，可能是参数的原因显得有点诡异后期调整。