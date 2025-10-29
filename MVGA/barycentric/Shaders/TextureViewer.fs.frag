out vec4 FragColor;
in  vec2 TexCoords;


uniform sampler2D fboAttachment;
uniform vec2 iResolution;
uniform float iTime;
void main()
{
/*
      vec3 c1=vec3(1.0,0.4,0.1);
        vec3 c2=vec3(1.0,0.8,0.1);
        vec2 p =gl_FragCoord.xy/iResolution.xy;
        p.x*=iResolution.x/iResolution.y;
        vec3 col = mix(c1,c2,p.y);
        vec2 q =p-vec2(0.35,0.7);
        float r =0.1;
        r+=0.045*cos(atan(q.x,q.y)*13-30.0*q.x +sin(iTime*3.14159));
        r+=0.01*sin(atan(q.x,q.y)*120.0);
        col*=dist_01(q,r);

        vec2 x = p-vec2(0.8, 0.2+0.4*cos(2.0*PI*iTime*0.0125));
        r=0.2;
        r+=0.01*cos(atan(x.x,x.y)*300.0);
        col+=vec3((1-dist_01(x,r))*0.25);

        r=0.012;
        r+=0.002*cos(q.y*150);
        r+=exp(-40.0*p.y);
        col*=1.0-(1.0-smoothstep(r,r+EPS,abs(q.x-0.075*sin(q.y*3.0))))*(1.0-smoothstep(0.0,0.1,q.y));



        float f= 0.1+smoothstep(0,0.6,0.6-x.y);

*/

    vec2 pos = gl_FragCoord.xy/iResolution;
    FragColor = texture(fboAttachment, pos);
    /*vec4 data = texelFetch(fboAttachment, ivec2(gl_FragCoord), 0);
        uint u = floatBitsToUint(data[0]);
        uint v = floatBitsToUint(data[1]);
            FragColor = vec4(sin(vec2(u, v)/64.0 + vec2(0.5, -0.7)*iTime), data[2] ,1.0);*/
}
