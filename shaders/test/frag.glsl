// afl_ext @ 2016
 

#ifdef GL_ES
precision highp float;
#endif

#extension GL_OES_standard_derivatives : enable

#define HOW_CLOUDY 0.5
#define SHADOW_THRESHOLD 0.2
#define SHADOW 0.2
#define SUBSURFACE 1.0
#define WIND_DIRECTION 2.0
#define TIME_SCALE 1.7
#define SCALE 0.23
#define ENABLE_SHAFTS

#define iGlobalTime time
#define iMouse (mouse.xy * resolution.xy)
#define iResolution resolution

mat2 RM = mat2(cos(WIND_DIRECTION), -sin(WIND_DIRECTION), sin(WIND_DIRECTION), cos(WIND_DIRECTION));
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float hash( float n )
{
    return fract(sin(n)*758.5453);
}

float noise( in vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x); 
    float n = p.x + p.y*57.0 + p.z*800.0;
    float res = mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x), mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
		    mix(mix( hash(n+800.0), hash(n+801.0),f.x), mix( hash(n+857.0), hash(n+858.0),f.x),f.y),f.z);
    return res;
}

float fbm( vec3 p )
{
    float f = 0.0;
    f += 0.50000*noise( p ); p = p*2.02;
    f -= 0.25000*noise( p ); p = p*2.03;
    f += 0.12500*noise( p ); p = p*3.01;
    f += 0.06250*noise( p ); p = p*3.04;
    f += 0.03500*noise( p ); p = p*4.01;
    f += 0.01250*noise( p ); p = p*4.04;
    f -= 0.00125*noise( p );
    return f/0.984375;
}

float cloud(vec3 p)
{
	p-=fbm(vec3(p.x,p.y,0.0)*0.3)*1.25;
	float a = min((fbm(p*1.0)*2.2-1.1), 0.0);
	return a*a;
}

float shadow = 1.0;


float clouds(vec2 p){
	float ic = cloud(vec3(p * 2.0, iGlobalTime*0.01 * TIME_SCALE)) / HOW_CLOUDY;
	float init = smoothstep(0.1, 1.0, ic) * 10.0;
	shadow = smoothstep(0.0, SHADOW_THRESHOLD, ic) * SHADOW + (1.0 - SHADOW);
	init = (init * cloud(vec3(p * (6.0), iGlobalTime*0.01 * TIME_SCALE)) * ic);
	init = (init * (cloud(vec3(p * (11.0), iGlobalTime*0.01 * TIME_SCALE))*0.5 + 0.4) * init);
	return min(1.0, init);
}
uniform sampler2D bb;
float cloudslowres(vec2 p){
	return 1.0 - (texture2D(bb, p).a - 0.9) * 10.0;
}

vec2 ratio = vec2(1.0, 1.0);

vec4 getresult(){
	vec2 surfacePosition = ((( gl_FragCoord.xy / iResolution.xy ) * vec2(iResolution.x / iResolution.y, 1.0)) * 2.0 - 1.0)*SCALE;
	vec2 position = ( surfacePosition);
	vec2 sun = ((iMouse.xy/ iResolution.xy)* vec2(iResolution.x / iResolution.y, 1.0)*2.0-1.0) * SCALE;
	float dst = distance(sun * ratio, position * ratio);
	float suni = pow(dst + 2., -100.0);
	float shaft =0.0;
	float st = 0.05;
	float w = 1.0;
	vec2 dir = sun - position;
	float c = clouds(position);
	#ifdef ENABLE_SHAFTS
	for(int i=0;i<20;i++){
		float occl = cloudslowres(clamp((gl_FragCoord.xy / iResolution.xy) + dir * st, 0.0, 1.0));
		w *= 0.9;
		st *= 1.2;
		shaft += max(0.0, (1.0 - occl)) * w;
	}
	#endif
    shadow = min(1.0, shadow + suni * suni * 0.2 * SUBSURFACE);
	suni *= (shaft * 0.3);
	return vec4(pow(mix(vec3(shadow), pow(vec3(0.23, 0.33, 0.48), vec3(2.2)) + suni, c), vec3(1.0/2.2)), c*0.1 + 0.9);		
}
 
void main( void ) {
	gl_FragColor = getresult().rgba;
}
