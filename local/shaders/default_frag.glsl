#version 330 core

in vec2 auv;
in vec3 vertex;

uniform vec2 resolution;
uniform float delta;
uniform float laguerre;

out vec4 FragColor;

float Hydrogen(vec3 p, vec3 pos, float a)
{
    float r = length(abs(pos - p));
    return pow(2.71828, -r/a)/(sqrt(3.1415926) * pow(a, 3/2));
}

int factorial(int n)
{
    int res = 1;
    for (int i = 2; i <= n; i++)
    res *= i;
    return res;
}

float sdGround(vec3 p)
{
    return p.y + 0.75f;
}

float map(vec3 p)
{
    return Hydrogen(p, vec3(0,0,1), 1);
}

float largest(float arr[80])
{
    float temp = 0;

    for(int i = 0; i < 80; i++)
    {
        if(arr[i] > temp)
        {
            temp = arr[i];
        }
    }

    return temp;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy * 2. - resolution.xy) / resolution.y;
    vec3 ro = vec3(0, 0, -3); //ray origin
    vec3 rd = normalize(vec3(uv, 1.0f)); //ray direction

    float t = 0.0f; //distance
    vec3 col = vec3(0.0);

    float values[80];

    //raymarching
    for(int i = 0; i < 80; i++)
    {
        vec3 p = ro + rd * t;

        float d = map(p);

        t += 0.1f;

        values[i] = d;
    }

    col = mix(vec3(0), vec3(1, 0.2f, 0.4f), largest(values));

    FragColor = vec4(col, 1.0f);
} 