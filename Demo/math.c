

#define Pi 3.14159

float g_result = 0;

float Add( float x, float y)
{
    g_result = x + y;
    return(g_result);
}

float Subtract( float x, float y)
{
    g_result = x - y;
    return(g_result);
}

float Multiply( float x, float y)
{
    g_result = x * y;
    return(g_result);
}

float Divide( float x, float y)
{
    g_result = x / y;
    return(g_result);
}
