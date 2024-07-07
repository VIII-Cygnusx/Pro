#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();


    //IMU
    virtual void IMU_RX();
    virtual void IMU_ANGLE(float* RX);
    virtual unsigned int STEP_RX();
    //IMU

    //OV7725
    void OV7725_sample();
    void OV7725_send2LCD(int x,int y);
    //OV7725

    //MAX30102
    void MAX30102_INIT();
    bool MAX30102_OK();
    void MAX30102_RX(int *RED,int *IR,int counter);
    void MAX30102_HR_OS(int *O2,int *HR);
    //MAX30102

    //SHT20
    void SHT20_RX(float *tem,float *hum);
    //SHT20


    //AP3216C
    float AP3216C_RX();
    //AP3216C

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
