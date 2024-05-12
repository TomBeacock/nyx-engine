cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
    matrix model;
    matrix projection;
    float padding[32];
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color: COLOR;
};

PS_INPUT VSMain(float3 position : POSITION, float3 color : COLOR)
{
    PS_INPUT ps_input;
    ps_input.position = mul(projection, mul(model, float4(position, 1.0)));
    ps_input.color = color;
    return ps_input;
}

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0);
}