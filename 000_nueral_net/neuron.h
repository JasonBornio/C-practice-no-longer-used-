#include <vector>

class Neuron {
    public:
        Neuron();
        

    private:
        float bias;
        std::vector<float> weights;
        

};

Neuron::Neuron(){
    bias = 0;
    
}