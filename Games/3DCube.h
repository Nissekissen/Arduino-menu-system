/**
 * @file 3DCube.h
 * 
 * @brief A 3D cube renderer for the menu system.
*/

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

/**
 * A struct for handling 3D vertices
 * 
 * @param x The x coordinate of the vertex
 * @param y The y coordinate of the vertex
 * @param z The z coordinate of the vertex
*/
struct Vertex3D
{
    float x, y, z = 0;

    Vertex3D(){};
    Vertex3D(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

/**
 * A struct for handling 2D vertices
 * 
 * @param x The x coordinate of the vertex
 * @param y The y coordinate of the vertex
*/
struct Vertex2D
{
    float x, y = 0;

    Vertex2D(){};
    Vertex2D(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

/**
 * A simple struct for handling edges easily
 * 
 * The edges are stored completely in 2D and thereby do not need to be converted
 * 
 * @param p1 The first vertex of the edge
 * @param p2 The second vertex of the edge
*/
struct Edge
{
    Vertex2D *p1;
    Vertex2D *p2;

    Edge(){};
    Edge(Vertex2D *_p1, Vertex2D *_p2)
    {
        p1 = _p1;
        p2 = _p2;
    }
};

/**
 * @brief A 3D cube renderer using the U8GLIB library
 * 
 * @param u8g U8GLIB_SSD1306_128X64 object for drawing to the screen
*/
class Cube
{
private:
    U8GLIB_SSD1306_128X64 *u8g;

    Vertex3D v[8];
    Vertex2D v2D[8];

    Edge e[12];

    int fl = 5;
    int sc = 10;

public:
    Cube(){};
    Cube(U8GLIB_SSD1306_128X64 *_u8g)
    {
        u8g = _u8g;

        v[0] = Vertex3D(1, 1, 1);
        v[1] = Vertex3D(1, -1, 1);
        v[2] = Vertex3D(-1, -1, 1);
        v[3] = Vertex3D(-1, 1, 1);
        v[4] = Vertex3D(1, 1, -1);
        v[5] = Vertex3D(1, -1, -1);
        v[6] = Vertex3D(-1, -1, -1);
        v[7] = Vertex3D(-1, 1, -1);
    }


    /**
     * Initialize the cube
    */
    void init()
    {
        v[0] = Vertex3D(1, 1, 1);
        v[1] = Vertex3D(1, -1, 1);
        v[2] = Vertex3D(-1, -1, 1);
        v[3] = Vertex3D(-1, 1, 1);
        v[4] = Vertex3D(1, 1, -1);
        v[5] = Vertex3D(1, -1, -1);
        v[6] = Vertex3D(-1, -1, -1);
        v[7] = Vertex3D(-1, 1, -1);

        for (int i = 0; i < 8; i++)
        {
            v2D[i] = projectPoint(v[i]);
        }

        e[0] = Edge(&v2D[0], &v2D[1]);
        e[1] = Edge(&v2D[1], &v2D[2]);
        e[2] = Edge(&v2D[2], &v2D[3]);
        e[3] = Edge(&v2D[3], &v2D[0]);
        e[4] = Edge(&v2D[4], &v2D[5]);
        e[5] = Edge(&v2D[5], &v2D[6]);
        e[6] = Edge(&v2D[6], &v2D[7]);
        e[7] = Edge(&v2D[7], &v2D[4]);
        e[8] = Edge(&v2D[4], &v2D[0]);
        e[9] = Edge(&v2D[1], &v2D[5]);
        e[10] = Edge(&v2D[2], &v2D[6]);
        e[11] = Edge(&v2D[3], &v2D[7]);

        sc = 10;
    }

    /**
     * Draw the cube to the screen
    */
    void draw()
    {
        for (int i = 0; i < 8; i++)
        {
            // u8g->drawCircle((v2D[i].x * 10) + 64, (v2D[i].y * 10) + 32, 1);
        }

        for (int i = 0; i < 12; i++)
        {
            u8g->drawLine((e[i].p1->x * sc) + 64,
                          (e[i].p1->y * sc) + 32,
                          (e[i].p2->x * sc) + 64,
                          (e[i].p2->y * sc) + 32);
        }
    }

    /**
     * Rotating the cube from user inputs.
    */
    void update()
    {
        if (digitalRead(2))
        {
            rotateY(PI / 16);
        }
        else if (digitalRead(3))
        {
            rotateY(PI / -16);
        }

        if (digitalRead(4))
        {
            rotateZ(PI / 16);
        }
        else if (digitalRead(5))
        {
            rotateZ(PI / -16);
        }

        for (int i = 0; i < 8; i++)
        {
            v2D[i] = projectPoint(v[i]);
        }
    }

    /**
     * Project a 3D point to a 2D point using planar perspective projection
     * 
     * @param p The 3D point to project
     * 
     * @return The 2D point
    */
    Vertex2D projectPoint(Vertex3D p)
    {
        Vertex2D proj;
        proj.x = fl * p.x / (fl + p.z);
        proj.y = fl * p.y / (fl + p.z);

        return proj;
    }

    
    /**
     * Rotate the cube around the Z axis
     *
     * @param angle The angle to rotate the cube by (radians)
    */
    void rotateY(double angle)
    {

        const tmm::Scalar rScalar[3][3] = {
            {cos(angle), 0, -sin(angle)},
            {0, 1, 0},
            {sin(angle), 0, cos(angle)}};

        tmm::SquareMatrix<3> rMatrix(rScalar);

        for (int i = 0; i < 8; i++)
        {
            const tmm::Scalar vScalar[1][3] = {
                {v[i].x, v[i].y, v[i].z}};

            tmm::Matrix<1, 3> vMatrix(vScalar);

            tmm::Matrix<1, 3> newMatrix = vMatrix * rMatrix;

            v[i].x = newMatrix.data[0][0];
            v[i].y = newMatrix.data[0][1];
            v[i].z = newMatrix.data[0][2];
        }
    }

    /**
     * Rotate the cube around the Z axis
     * 
     * @param angle The angle to rotate the cube by (radians)
    */
    void rotateZ(double angle)
    {

        const tmm::Scalar rScalar[3][3] = {
            {cos(angle), -sin(angle), 0},
            {sin(angle), cos(angle), 0},
            {0, 0, 1}};

        tmm::SquareMatrix<3> rMatrix(rScalar);

        for (int i = 0; i < 8; i++)
        {
            const tmm::Scalar vScalar[1][3] = {
                {v[i].x, v[i].y, v[i].z}};

            tmm::Matrix<1, 3> vMatrix(vScalar);

            tmm::Matrix<1, 3> newMatrix = vMatrix * rMatrix;

            v[i].x = newMatrix.data[0][0];
            v[i].y = newMatrix.data[0][1];
            v[i].z = newMatrix.data[0][2];
        }
    }
};