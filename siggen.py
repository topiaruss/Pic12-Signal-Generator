#Creates a C constant table for a sine wave approximation but with 
# the bits move around to suit the port layout on the PIC12 
# 2011-01-29
# Russ Ferriday
# 
import math
TRESOLUTION = 64 # time resolution
BRESOLUTION = 64 # bit resolution - so we can do math on the output
PRESOLUTION = 32 # port resolution

def shuffle(inted):
    # move bit 3 to bit 5
    inted = (inted & 0x37) | ((inted & 8) and 32) 
    #inted = (inted & 0x37) | ((inted & 8) and 4)
    return inted
    
vals=[]
for phi in range (TRESOLUTION):
    sw = math.sin( (phi/float(TRESOLUTION)) * 2.0 * math.pi)
    shifted = sw + 1.0
    scaled = shifted/2.0 - 0.01 
    # scaled, 
    inted = int(math.trunc(scaled*BRESOLUTION + 0.5))
    vals.append(inted)
    
#just for debug 
if 0:
    for inted in vals:
        print inted;
    
#output the sine values, in 6 bits, to allow more accuracy in mixing
print """
char const sine[] = {"""
valcount = 0   
for inted in vals:
    #print bin(inted),
    #print bin(shuffle(inted))
    print ' 0x%02x,' % inted,
    valcount +=1;
    if valcount %8 == 0:
        print
print"};"

#and then the bit shuffle lookup table for fast conversion of the 
# sine wave to match the unusual port pin assignments, forced because
# of GPIO3 being used for _MCLR
print """
char const map[] = {"""
valcount = 0   
for phi in range (PRESOLUTION):
    val = shuffle(phi)
    assert( val & 8 == 0 )
    print ' 0x%02x,' % val,
    valcount +=1;
    if valcount %8 == 0:
        print
print "};"