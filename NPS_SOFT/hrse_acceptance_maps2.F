**********************************************************************
*
* Hall A HRS-E acceptance subroutine for Monte-Carlo studies. 
*
* Author: Stephanie JAMINION, LPC-Clermont. April 1999. Fortran77.
*
**********************************************************************
******* This program was realized using the results of program "snake"
******* with quadripole field maps and dipole model of John Lerose
******* at momentum equal at 3.496 GeV.
******* It allows to determine if a particle of given target coordinates
******* is in the acceptance of the spectrometer (i.e. reaches the VDCs).
*
* input argts = target vector x(i),(i=1,5) in Transport spectrometer frame.
* consider a particle of momentum vector P=(Px,Py,Pz).
*
*** x(1) = x_tg  of Espace = vertical extension of the track in
*                            [z=0] plane (mm)
*** x(2) = th_tg of Espace = tan(Px/Pz) = (tangent of) angle of particle
*                            track in the dispersive plane (radians)
*
*
*** x(3) = y_tg  of Espace = non-dispersive horizontal position in 
*                             [z=0] plane (mm)
*** x(4) = ph_tg of Espace = tan(Py/Pz) = (tangent of) angle of particle 
*                             track in the non-dispersive plane (radians)
*** x(5) = delta_p/p of Espace = momentum of particle relative to the 
*                                central ray
*                 
*                                       
**** frame :  y_tg   <-----------|o       (z_tg=spectrometer axis
*                                | 
*                                |
*                                |        (Transport convention)
*                                |
*                                |   
*                                V  x_tg
*
* angles: th_tg >0 when momentum vector points towards (+x_tg) (down)
*         ph_tg >0 when momentum vector points towards (+y_tg)     
*
* output argt: accepted=0 (rejected) or 1 (accepted).
*

      subroutine hrse_acceptance_maps2(x,accepted)

      integer accepted
      real x(5)

      real r2_1,r2_4,r2_9 ,r2_12b ! normalized radius for circle
                                  ! for Q1 cuts
      real r2_12,r2_15,r2_17      ! for Q2 cuts    
      real x22, z22               ! dipole cut
      real a22, b22
      real x24, z24               ! dipole cut
      real a24, b24
      real x26, z26               ! dipole cut
      real a26, b26
      real r2_29, r2_32, r2_34    ! for Q3 cuts
      real x37, z37             ! VDC cuts : u1 plane
      real x38, z38             ! VDC cuts : u2 plane

      accepted=0      
      a22 = 21.4233871
      b22 = -2422.596613
      a24 = 24.51747312
      b24 = -1336.95586
      a26 = 82.77419355
      b26 = 10346.77419

 
      r2_1 = ep1(x,5)    
      if (r2_1.ge.1) return
         
      r2_4 = ep4(x,5)
      if (r2_4.ge.1.) return
         
      r2_9 = ep9(x,5)
      if (r2_9.ge.1.) return

      r2_12b = ep12b(x,5)
      if (r2_12b.ge.1.) return

      r2_12 = ep12(x,5)
      if (r2_12.ge.1.) return

      r2_15 = ep15(x,5)
      if (r2_15.ge.1.) return

      r2_17 = ep17(x,5)
      if (r2_17.ge.1.) return

      x22 = ep22x(x,5)
      z22 = ep22z(x,5)
      if ((x22.ge.-4941.13).or.(x22.le.-5259.91).or. 
     >        (x22.ge.(a22*z22+b22)).or.(x22.ge.(-a22*z22+b22))) 
     >     return

      x24 = ep24x(x,5)
      z24 = ep24z(x,5)
      if ((x24.ge.-4219.23).or.(x24.le.-4584.05).or. 
     >        (x24.ge.(a24*z24+b24)).or.(x24.ge.(-a24*z24+b24))) 
     >     return

      x26 = ep26x(x,5)
      z26 = ep26z(x,5)
      if ((x26.ge.615.84).or.(x26.le.-615.84).or. 
     >        (x26.ge.(a26*z26+b26)).or.(x26.ge.(-a26*z26+b26))) 
     >     return

      r2_29 = ep29(x,5)
      if (r2_29.ge.1.) return

      r2_32 = ep32(x,5)
      if (r2_32.ge.1.) return

      r2_34 = ep34(x,5)
      if (r2_34.ge.1.) return

      x37 = ep37x(x,5)
      z37 = ep37z(x,5)
      if ((x37.ge.678.77).or.(x37.le.-629.39).or. 
     >        (z37.ge.100.0).or.(z37.le.-100.0)) return

      x38 = ep38x(x,5)
      z38 = ep38z(x,5)
      if ((x38.lt.774.22).and.(x38.gt.-724.84).and. 
     >        (z38.lt.100.0).and.(z38.gt.-100.0)) accepted = 1



      end   ! END of subroutine

**********************************************************************
*list of funtions
**********************************************************************

      function ep1   (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff( 9)
      data ncoeff/  8/
      data avdat/   .4037825E+00/
      data xmin/
     1  -.50000E+01, -.80000E-01, -.60000E+02, -.50161E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .80000E-01,  .60000E+02,  .50161E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.40380046E+00,  .43315971E+00,  .17041370E+00,  .33006823E+00,
     +   .15989172E+00,  .43963645E-01,  .11123376E-02,  .18633550E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
c          set up monomials   functions
      x11 = x1
      x12 = x11*x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x41 = x4
      x42 = x41*x4
c
c                  function
c
      ep1   =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)        *x31*x41    
     5  +coeff( 5)        *x32        
     6  +coeff( 6)*x11*x21            
     7  +coeff( 7)*x12                
     8  +coeff( 8)    *x24            
c
      return
      end

****************************************************************************
      function ep4   (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(30)
      data ncoeff/ 29/
      data avdat/   .1044047E+01/
      data xmin/
     1  -.50000E+01, -.80000E-01, -.60000E+02, -.50161E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .80000E-01,  .60000E+02,  .50161E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.10441881E+01,  .10848902E+01,  .52700406E+00,  .65073967E-01,
     +   .61724359E+00,  .40144362E-02,  .18090864E+00,  .84660063E-02,
     +  -.47818180E-02, -.46152574E-04, -.38018397E-02,  .99207391E-03,
     +  -.14988786E-02,  .11446739E-02,  .54766401E-03,  .35542858E-03,
     +  -.85133646E-03,  .39046408E-05,  .71293506E-03,  .11032493E-02,
     +   .86797919E-03, -.85338752E-03, -.24058742E-02, -.11863592E-03,
     +   .12555299E-03,  .19668591E-03,  .12262579E-03, -.11838509E-02,
     +   .26917746E-03,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up monomials   functions
      x11 = x1
      x12 = x11*x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x41 = x4
      x42 = x41*x4
      x43 = x42*x4
      x44 = x43*x4
      x51 = x5
      x52 = x51*x5
c
c                  function
c
      ep4   =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)*x11*x21            
     5  +coeff( 5)        *x31*x41    
     6  +coeff( 6)    *x24            
     7  +coeff( 7)        *x32        
     8  +coeff( 8)    *x22        *x51
      ep4   =ep4   
     9  +coeff( 9)        *x31*x41*x51
     1  +coeff(10)                *x51
     2  +coeff(11)            *x42*x51
     3  +coeff(12)*x12                
     4  +coeff(13)        *x32    *x51
     5  +coeff(14)    *x22*x31*x41    
     6  +coeff(15)*x11*x21        *x51
     7  +coeff(16)                *x52
     8  +coeff(17)    *x22        *x52
      ep4   =ep4   
     9  +coeff(18)    *x21            
     1  +coeff(19)    *x22    *x42    
     2  +coeff(20)            *x44    
     3  +coeff(21)        *x31*x43    
     4  +coeff(22)    *x22*x32        
     5  +coeff(23)    *x24*x31*x41    
     6  +coeff(24)    *x23            
     7  +coeff(25)    *x21*x31*x41    
     8  +coeff(26)*x11*x23            
      ep4   =ep4   
     9  +coeff(27)    *x23    *x42    
     1  +coeff(28)    *x24    *x42    
     2  +coeff(29)        *x32*x42    
c
      return
      end
****************************************************************************
      function ep9   (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(43)
      data ncoeff/ 42/
      data avdat/   .1184685E+01/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50122E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50122E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.11850723E+01,  .92962998E+00,  .16220107E+01,  .14983183E+01,
     +  -.36247021E-02,  .34628090E+00,  .50100159E-01, -.59216648E-01,
     +   .18538449E-04,  .20233094E-03, -.62864423E-01,  .52439551E-04,
     +  -.16599083E-01,  .37126884E-01,  .27423322E-02, -.10998559E-01,
     +   .12146050E-04, -.26155279E-02,  .20739562E-02,  .10242040E-01,
     +  -.42905216E-03, -.13356177E-01,  .12176003E-01, -.45635207E-02,
     +   .45038117E-02,  .52890312E-02, -.53104199E-04, -.18161008E-05,
     +   .93059946E-03,  .37145620E-03,  .95040500E-02,  .14263820E-02,
     +  -.13847357E-03,  .77789049E-02, -.72086434E-03,  .49077556E-02,
     +   .20537861E-02, -.94661117E-03,  .25899550E-02,  .18404934E-02,
     +   .15547827E-02, -.52297267E-03,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up monomials   functions
      x11 = x1
      x12 = x11*x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x41 = x4
      x42 = x41*x4
      x43 = x42*x4
      x44 = x43*x4
      x51 = x5
      x52 = x51*x5
c
c                  function
c
      ep9   =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)        *x31*x41    
     5  +coeff( 5)    *x24            
     6  +coeff( 6)        *x32        
     7  +coeff( 7)    *x22        *x51
     8  +coeff( 8)            *x42*x51
      ep9   =ep9   
     9  +coeff( 9)*x11*x23            
     1  +coeff(10)*x11*x21    *x42    
     2  +coeff(11)        *x31*x41*x51
     3  +coeff(12)*x11*x21*x31*x41    
     4  +coeff(13)        *x32    *x51
     5  +coeff(14)*x11*x21            
     6  +coeff(15)*x11*x21        *x51
     7  +coeff(16)    *x22    *x42    
     8  +coeff(17)                *x52
      ep9   =ep9   
     9  +coeff(18)    *x22        *x52
     1  +coeff(19)    *x21*x31*x41    
     2  +coeff(20)            *x44    
     3  +coeff(21)    *x21*x32        
     4  +coeff(22)    *x22*x31*x41    
     5  +coeff(23)        *x31*x43    
     6  +coeff(24)    *x22*x32        
     7  +coeff(25)        *x32*x42    
     8  +coeff(26)        *x31*x41*x52
      ep9   =ep9   
     9  +coeff(27)    *x22    *x42*x52
     1  +coeff(28)            *x44*x52
     2  +coeff(29)    *x21    *x42    
     3  +coeff(30)*x12                
     4  +coeff(31)    *x24*x31*x41    
     5  +coeff(32)        *x32    *x52
     6  +coeff(33)    *x21            
     7  +coeff(34)    *x24    *x42    
     8  +coeff(35)    *x24        *x51
      ep9   =ep9   
     9  +coeff(36)            *x42*x52
     1  +coeff(37)    *x21*x32*x42    
     2  +coeff(38)    *x23    *x44    
     3  +coeff(39)    *x24*x32        
     4  +coeff(40)    *x23*x31*x41    
     5  +coeff(41)    *x23*x32        
     6  +coeff(42)        *x31*x43*x51
c
      return
      end
****************************************************************************
      function ep12  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(36)
      data ncoeff/ 35/
      data avdat/   .1420827E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.14209238E+00,  .22992741E+00,  .53230673E+00,  .46757800E-05,
     +   .47261998E+00,  .10494943E+00,  .73110927E-02,  .16046545E-01,
     +  -.22525994E-01, -.23601791E-01, -.60372218E-02,  .81942149E-03,
     +   .77391211E-04,  .36934300E-02,  .45133373E-02,  .19912904E-02,
     +  -.76341996E-03,  .19262765E-02,  .20575391E-02,  .53670479E-03,
     +   .68075125E-04, -.14177815E-03,  .31202612E-03,  .58348392E-04,
     +  -.10086838E-02,  .38666226E-03, -.22715687E-04,  .16758226E-03,
     +   .37165871E-03,  .13494848E-02, -.25954563E-02, -.26277245E-02,
     +  -.79900742E-03, -.10921571E-03,  .75862865E-03,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up monomials   functions
      x11 = x1
      x12 = x11*x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x33 = x32*x3
      x41 = x4
      x42 = x41*x4
      x43 = x42*x4
      x44 = x43*x4
      x51 = x5
      x52 = x51*x5
c
c                  function
c
      ep12  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)                *x51
     5  +coeff( 5)        *x31*x41    
     6  +coeff( 6)        *x32        
     7  +coeff( 7)*x11*x21            
     8  +coeff( 8)    *x22        *x51
      ep12  =ep12  
     9  +coeff( 9)            *x42*x51
     1  +coeff(10)        *x31*x41*x51
     2  +coeff(11)        *x32    *x51
     3  +coeff(12)*x11*x21        *x51
     4  +coeff(13)    *x21    *x42    
     5  +coeff(14)            *x44    
     6  +coeff(15)        *x31*x43    
     7  +coeff(16)        *x32*x42    
     8  +coeff(17)    *x22        *x52
      ep12  =ep12  
     9  +coeff(18)            *x42*x52
     1  +coeff(19)        *x31*x41*x52
     2  +coeff(20)        *x32    *x52
     3  +coeff(21)    *x21            
     4  +coeff(22)    *x23            
     5  +coeff(23)    *x21*x32        
     6  +coeff(24)*x12                
     7  +coeff(25)    *x24            
     8  +coeff(26)        *x33*x41    
      ep12  =ep12  
     9  +coeff(27)    *x23*x31*x41    
     1  +coeff(28)    *x23*x32        
     2  +coeff(29)    *x23*x31*x43    
     3  +coeff(30)    *x21*x31*x41    
     4  +coeff(31)    *x22    *x42    
     5  +coeff(32)    *x22*x31*x41    
     6  +coeff(33)    *x22*x32        
     7  +coeff(34)*x11*x23            
     8  +coeff(35)    *x21*x32*x42    
c
      return
      end
****************************************************************************
      function ep12b (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(46)
      data ncoeff/ 45/
      data avdat/   .9377591E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .80074441E+00,  .10728556E+01,  .19027480E+01,  .16704255E-02,
     +   .29096436E-01,  .45559821E+00,  .21103397E+00, -.95818043E-01,
     +  -.23654943E-03,  .32178476E-01, -.12321067E-01, -.67012082E-03,
     +  -.20181029E-04, -.25509795E-01, -.45823943E-01,  .33420548E-02,
     +  -.76436810E-03,  .36715716E-02,  .87548457E-02,  .28064682E-02,
     +   .12157365E-03,  .11257486E-02,  .20063510E-02,  .99174271E-03,
     +  -.53844234E-03,  .23567711E-02,  .16626243E-02,  .16125808E-03,
     +  -.20683699E-02,  .40291240E-02,  .12215857E-02,  .52529550E-03,
     +   .16840441E-03, -.72686956E-03,  .18781138E-02,  .87364017E-04,
     +   .23857641E-04, -.29045856E-03, -.50267477E-04,  .20569143E-04,
     +   .32035976E-04, -.17247341E-04,  .18449231E-04,  .12525129E-03,
     +  -.93009949E-04,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep12b =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)            *x42    
     3  +coeff( 3)        *x31*x41    
     4  +coeff( 4)            *x44    
     5  +coeff( 5)*x11*x21            
     6  +coeff( 6)    *x22            
     7  +coeff( 7)        *x32        
     8  +coeff( 8)        *x31*x41*x51
      ep12b =ep12b 
     9  +coeff( 9)            *x44*x51
     1  +coeff(10)    *x22        *x51
     2  +coeff(11)        *x32    *x51
     3  +coeff(12)        *x31*x43*x51
     4  +coeff(13)    *x22    *x42*x51
     5  +coeff(14)                *x51
     6  +coeff(15)            *x42*x51
     7  +coeff(16)*x11*x21        *x51
     8  +coeff(17)    *x22        *x52
      ep12b =ep12b 
     9  +coeff(18)        *x31*x43    
     1  +coeff(19)    *x21*x31*x41    
     2  +coeff(20)    *x21            
     3  +coeff(21)*x12                
     4  +coeff(22)        *x32*x42    
     5  +coeff(23)    *x21*x32        
     6  +coeff(24)    *x21*x31*x43    
     7  +coeff(25)    *x22*x32        
     8  +coeff(26)    *x21    *x42    
      ep12b =ep12b 
     9  +coeff(27)                *x52
     1  +coeff(28)    *x21    *x44    
     2  +coeff(29)    *x22*x31*x41    
     3  +coeff(30)        *x31*x41*x52
     4  +coeff(31)    *x21*x32*x42    
     5  +coeff(32)        *x32    *x52
     6  +coeff(33)*x11*x21    *x42    
     7  +coeff(34)    *x22    *x42    
     8  +coeff(35)            *x42*x52
      ep12b =ep12b 
     9  +coeff(36)*x11    *x31*x41    
     1  +coeff(37)*x12            *x51
     2  +coeff(38)        *x32*x42*x51
     3  +coeff(39)*x11*x21        *x52
     4  +coeff(40)*x11                
     5  +coeff(41)    *x21    *x42*x51
     6  +coeff(42)*x11*x22            
     7  +coeff(43)*x11    *x32        
     8  +coeff(44)*x11*x21*x31*x41    
      ep12b =ep12b 
     9  +coeff(45)    *x21*x31*x41*x51
c
      return
      end
****************************************************************************
      function ep15  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(34)
      data ncoeff/ 33/
      data avdat/   .3766205E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.37664688E+00,  .26448941E+00,  .13792418E+01,  .10740354E+01,
     +   .20929034E+00, -.47353995E-02,  .40452510E-01, -.66847675E-01,
     +  -.68807878E-01, -.16656842E-01,  .35874825E-03, -.17723376E-01,
     +  -.63622342E-05, -.15641540E-01,  .11488793E-02, -.11981317E-02,
     +   .22166914E-03, -.27909974E-03,  .76792911E-02,  .17720156E-02,
     +   .84245000E-02,  .10093232E-01, -.37290268E-02, -.29710799E-02,
     +   .17894643E-03,  .32159023E-03,  .54833535E-02,  .58655231E-02,
     +   .14953183E-02,  .43305387E-02,  .10502920E-02,  .62002736E-03,
     +  -.28842890E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up monomials   functions
      x11 = x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x33 = x32*x3
      x41 = x4
      x42 = x41*x4
      x43 = x42*x4
      x44 = x43*x4
      x51 = x5
      x52 = x51*x5
c
c                  function
c
      ep15  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)        *x31*x41    
     5  +coeff( 5)        *x32        
     6  +coeff( 6)*x11*x21            
     7  +coeff( 7)    *x22        *x51
     8  +coeff( 8)            *x42*x51
      ep15  =ep15  
     9  +coeff( 9)        *x31*x41*x51
     1  +coeff(10)        *x32    *x51
     2  +coeff(11)    *x21    *x42    
     3  +coeff(12)    *x22    *x42    
     4  +coeff(13)                *x52
     5  +coeff(14)    *x22*x31*x41    
     6  +coeff(15)*x11*x21        *x51
     7  +coeff(16)    *x22        *x52
     8  +coeff(17)    *x21            
      ep15  =ep15  
     9  +coeff(18)    *x23            
     1  +coeff(19)    *x21*x31*x41    
     2  +coeff(20)    *x21*x32        
     3  +coeff(21)            *x44    
     4  +coeff(22)        *x31*x43    
     5  +coeff(23)    *x22*x32        
     6  +coeff(24)    *x24            
     7  +coeff(25)    *x21*x31*x43    
     8  +coeff(26)    *x21*x32*x42    
      ep15  =ep15  
     9  +coeff(27)            *x42*x52
     1  +coeff(28)        *x31*x41*x52
     2  +coeff(29)        *x32    *x52
     3  +coeff(30)        *x32*x42    
     4  +coeff(31)        *x33*x41    
     5  +coeff(32)    *x21    *x44    
     6  +coeff(33)    *x21*x33*x41    
c
      return
      end
****************************************************************************
      function ep17  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(53)
      data ncoeff/ 52/
      data avdat/   .5448138E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.54484296E+00,  .59326452E+00,  .12994490E+01,  .17988676E-04,
     +  -.28286483E-01,  .92118883E+00, -.96320277E-02,  .16349950E+00,
     +  -.56084491E-01,  .96334442E-01,  .75300438E-02,  .10044799E-01,
     +   .15496973E-04,  .25393066E-02, -.59901379E-01,  .23083910E-02,
     +  -.12644022E-01, -.14558971E-01, -.55234949E-02, -.15774929E-02,
     +   .27846370E-01,  .14572580E-01, -.46823472E-02,  .34812696E-01,
     +   .13063414E-01,  .80338801E-03,  .35771762E-03, -.94643427E-03,
     +  -.49089432E-01, -.23643293E-02,  .93717575E-02, -.17613245E-02,
     +   .12342472E-01, -.32443140E-01, -.10808940E-02, -.21375038E-01,
     +  -.57934844E-02, -.13739354E-02,  .15050882E-01,  .93012014E-02,
     +  -.25419665E-02, -.10776916E-03,  .65333548E-03,  .48799827E-02,
     +   .18932389E-02, -.54322239E-01,  .46230229E-02,  .20571219E-03,
     +  -.22231352E-01,  .84884968E-02,  .19681391E-02,  .12514007E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up monomials   functions
      x11 = x1
      x12 = x11*x1
      x21 = x2
      x22 = x21*x2
      x23 = x22*x2
      x24 = x23*x2
      x31 = x3
      x32 = x31*x3
      x41 = x4
      x42 = x41*x4
      x43 = x42*x4
      x44 = x43*x4
      x51 = x5
      x52 = x51*x5
c
c                  function
c
      ep17  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x22            
     3  +coeff( 3)            *x42    
     4  +coeff( 4)                *x51
     5  +coeff( 5)*x11*x21            
     6  +coeff( 6)        *x31*x41    
     7  +coeff( 7)    *x24            
     8  +coeff( 8)        *x32        
      ep17  =ep17  
     9  +coeff( 9)    *x22    *x42    
     1  +coeff(10)    *x22        *x51
     2  +coeff(11)            *x42*x51
     3  +coeff(12)    *x21*x31*x41    
     4  +coeff(13)                *x52
     5  +coeff(14)    *x21*x32        
     6  +coeff(15)    *x22*x31*x41    
     7  +coeff(16)*x11*x21        *x51
     8  +coeff(17)        *x31*x41*x51
      ep17  =ep17  
     9  +coeff(18)    *x22*x32        
     1  +coeff(19)        *x32    *x51
     2  +coeff(20)    *x23            
     3  +coeff(21)    *x24    *x42    
     4  +coeff(22)    *x21*x31*x43    
     5  +coeff(23)    *x22        *x52
     6  +coeff(24)    *x24*x31*x41    
     7  +coeff(25)    *x21*x32*x42    
     8  +coeff(26)    *x21            
      ep17  =ep17  
     9  +coeff(27)*x12                
     1  +coeff(28)*x11*x23            
     2  +coeff(29)    *x22    *x44    
     3  +coeff(30)            *x42*x52
     4  +coeff(31)    *x24*x32        
     5  +coeff(32)        *x31*x43    
     6  +coeff(33)    *x21    *x44    
     7  +coeff(34)    *x23    *x44    
     8  +coeff(35)        *x31*x41*x52
      ep17  =ep17  
     9  +coeff(36)    *x23*x31*x43    
     1  +coeff(37)    *x21    *x42    
     2  +coeff(38)            *x44    
     3  +coeff(39)    *x23    *x42    
     4  +coeff(40)    *x23*x31*x41    
     5  +coeff(41)        *x32*x42    
     6  +coeff(42)*x12            *x51
     7  +coeff(43)    *x24        *x51
     8  +coeff(44)    *x22    *x42*x51
      ep17  =ep17  
     9  +coeff(45)    *x23*x32        
     1  +coeff(46)    *x22*x31*x43    
     2  +coeff(47)    *x22*x31*x41*x51
     3  +coeff(48)*x11*x21        *x52
     4  +coeff(49)    *x22*x32*x42    
     5  +coeff(50)    *x24    *x44    
     6  +coeff(51)        *x32*x44    
     7  +coeff(52)    *x22*x32    *x51
c
      return
      end
****************************************************************************
      function ep22x (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(60)
      data ncoeff/ 59/
      data avdat/  -.5097025E+04/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.12708360E+01, -.14019246E+03,  .54074912E+01,  .25882821E+01,
     +  -.12424387E+02, -.73935312E+00, -.43275157E+00,  .63769251E+00,
     +   .34492931E+00, -.18896646E+01,  .16563635E+01, -.46661058E+00,
     +   .41906756E+00,  .28671312E+01,  .42134583E+00, -.11827161E+01,
     +  -.61703587E+00, -.19303976E+01, -.96811408E+00,  .13746078E+00,
     +  -.21839467E+00, -.33486483E+00, -.19779935E+00, -.54033339E-01,
     +  -.73860615E+00,  .96842032E-02,  .37641998E-01, -.12235044E+01,
     +   .78496210E-01, -.13597175E+00,  .37899658E+00, -.23692586E-01,
     +   .87640166E-01,  .15161574E+00,  .89827821E-01,  .17374074E-02,
     +   .20521207E-01, -.85612111E-01,  .12650816E+00,  .20908942E-01,
     +  -.63380538E-02, -.30935666E-01,  .43859445E-02, -.12191008E-01,
     +   .11723156E+00,  .12176678E-01, -.15939159E-01, -.14044290E-01,
     +   .53241786E-01,  .66192649E-01, -.19902134E-01, -.81662824E-02,
     +   .73548672E-02,  .41221622E-02,  .54605585E-01, -.12956539E-01,
     +  -.41592857E-02, -.45818482E-02, -.52608657E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep22x =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)*x11                
     4  +coeff( 4)    *x22            
     5  +coeff( 5)    *x21        *x51
     6  +coeff( 6)*x11            *x51
     7  +coeff( 7)*x11*x21            
     8  +coeff( 8)    *x21        *x52
      ep22x =ep22x 
     9  +coeff( 9)                *x51
     1  +coeff(10)        *x31*x41    
     2  +coeff(11)    *x21    *x42    
     3  +coeff(12)        *x32        
     4  +coeff(13)    *x22        *x51
     5  +coeff(14)    *x21*x31*x41    
     6  +coeff(15)    *x21*x32        
     7  +coeff(16)    *x23    *x42    
     8  +coeff(17)            *x42    
      ep22x =ep22x 
     9  +coeff(18)    *x23*x31*x41    
     1  +coeff(19)    *x23            
     2  +coeff(20)*x11*x22            
     3  +coeff(21)        *x31*x43    
     4  +coeff(22)        *x32*x42    
     5  +coeff(23)    *x23*x32        
     6  +coeff(24)            *x42*x51
     7  +coeff(25)    *x21    *x42*x51
     8  +coeff(26)    *x22*x32        
      ep22x =ep22x 
     9  +coeff(27)*x11            *x52
     1  +coeff(28)    *x21*x31*x41*x51
     2  +coeff(29)    *x24    *x42    
     3  +coeff(30)    *x21*x32    *x51
     4  +coeff(31)    *x24*x31*x41    
     5  +coeff(32)    *x23    *x42*x51
     6  +coeff(33)    *x24*x32        
     7  +coeff(34)    *x24            
     8  +coeff(35)*x11        *x42    
      ep22x =ep22x 
     9  +coeff(36)    *x22    *x42    
     1  +coeff(37)*x11*x21        *x51
     2  +coeff(38)    *x23        *x51
     3  +coeff(39)*x11    *x31*x41    
     4  +coeff(40)        *x32    *x51
     5  +coeff(41)    *x21*x31*x43    
     6  +coeff(42)        *x31*x43*x51
     7  +coeff(43)*x12                
     8  +coeff(44)                *x52
      ep22x =ep22x 
     9  +coeff(45)    *x22*x31*x41    
     1  +coeff(46)*x11    *x32        
     2  +coeff(47)*x11*x22        *x51
     3  +coeff(48)    *x22        *x52
     4  +coeff(49)*x11*x22    *x42    
     5  +coeff(50)    *x21*x32*x42    
     6  +coeff(51)    *x21    *x42*x52
     7  +coeff(52)*x11*x21    *x42    
     8  +coeff(53)*x11*x24            
      ep22x =ep22x 
     9  +coeff(54)*x12*x21        *x51
     1  +coeff(55)*x11*x22*x31*x41    
     2  +coeff(56)    *x22*x31*x43    
     3  +coeff(57)*x12*x22        *x51
     4  +coeff(58)*x11*x24        *x51
     5  +coeff(59)*x11    *x32    *x51
c
      return
      end
****************************************************************************
      function ep22z (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(60)
      data ncoeff/ 59/
      data avdat/   .0000000E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.50063E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .50063E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.20194980E+03, -.33684593E+02,  .39480507E+01, -.33972954E+02,
     +  -.10625276E+02, -.24649086E+01, -.11387216E+02, -.86284676E+01,
     +   .15980044E+02,  .97107878E+01, -.70360303E+00,  .17608925E+01,
     +  -.31062225E+00,  .73633009E+00,  .79248695E+01,  .16860871E+01,
     +   .41277142E+01,  .88958359E+01,  .29429704E+00,  .17534867E+00,
     +   .22360961E+01,  .48409721E+00,  .27813315E+01, -.13901064E+01,
     +   .19594979E+00, -.17172879E+00, -.10993447E+01, -.12498128E+00,
     +  -.25817403E+00, -.14998569E+01, -.22163860E+00, -.59389465E-01,
     +   .60642015E-01, -.91968584E+00, -.14732692E+00, -.53601485E+00,
     +   .75104631E-01, -.75062168E+00, -.81312485E-01, -.12175746E+00,
     +   .10594986E+00,  .17696550E-01, -.11902016E+00, -.61196104E-01,
     +   .28030509E-02,  .13294791E+00, -.14218321E-01,  .20271726E+00,
     +  -.20768331E-01, -.79385087E-01,  .36682706E-01,  .79035848E-01,
     +   .47187444E-01, -.51966131E-01,  .50619777E-01,  .45247331E-01,
     +   .13152869E-01, -.27756441E-01,  .64953804E-01,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep22z =avdat
     1  +coeff( 1)            *x41    
     2  +coeff( 2)        *x31        
     3  +coeff( 3)            *x43    
     4  +coeff( 4)            *x41*x51
     5  +coeff( 5)        *x31    *x51
     6  +coeff( 6)    *x21*x31*x42    
     7  +coeff( 7)    *x21    *x41    
     8  +coeff( 8)    *x21*x31        
      ep22z =ep22z 
     9  +coeff( 9)    *x22    *x41    
     1  +coeff(10)    *x22*x31        
     2  +coeff(11)    *x24    *x41    
     3  +coeff(12)            *x41*x52
     4  +coeff(13)    *x24*x31        
     5  +coeff(14)        *x31    *x52
     6  +coeff(15)        *x31*x42    
     7  +coeff(16)    *x21    *x41*x51
     8  +coeff(17)    *x22    *x43    
      ep22z =ep22z 
     9  +coeff(18)    *x22*x31*x42    
     1  +coeff(19)*x11        *x41    
     2  +coeff(20)*x11    *x31        
     3  +coeff(21)        *x32*x41    
     4  +coeff(22)    *x21*x31    *x51
     5  +coeff(23)    *x22*x32*x41    
     6  +coeff(24)    *x23    *x41    
     7  +coeff(25)*x11*x23    *x41    
     8  +coeff(26)        *x32*x43    
      ep22z =ep22z 
     9  +coeff(27)    *x23*x31        
     1  +coeff(28)*x11        *x41*x51
     2  +coeff(29)    *x22    *x41*x51
     3  +coeff(30)    *x21*x32*x41    
     4  +coeff(31)    *x23    *x43    
     5  +coeff(32)*x11    *x31    *x51
     6  +coeff(33)*x11*x23*x31        
     7  +coeff(34)    *x23*x31*x42    
     8  +coeff(35)    *x24    *x41*x51
      ep22z =ep22z 
     9  +coeff(36)    *x23*x32*x41    
     1  +coeff(37)    *x22*x31*x44    
     2  +coeff(38)    *x21    *x43    
     3  +coeff(39)        *x31*x44    
     4  +coeff(40)    *x22*x31    *x51
     5  +coeff(41)*x11*x21    *x41*x51
     6  +coeff(42)*x11*x23    *x43    
     7  +coeff(43)    *x21*x32*x43    
     8  +coeff(44)    *x24*x31    *x51
      ep22z =ep22z 
     9  +coeff(45)*x11*x22    *x41    
     1  +coeff(46)            *x43*x51
     2  +coeff(47)*x11*x21    *x43    
     3  +coeff(48)        *x31*x42*x51
     4  +coeff(49)*x11*x24    *x41    
     5  +coeff(50)    *x21*x31*x44    
     6  +coeff(51)*x11*x21*x31    *x51
     7  +coeff(52)        *x32*x41*x51
     8  +coeff(53)    *x22    *x43*x51
      ep22z =ep22z 
     9  +coeff(54)    *x22    *x41*x52
     1  +coeff(55)            *x43*x52
     2  +coeff(56)    *x21*x32*x41*x51
     3  +coeff(57)    *x23    *x43*x51
     4  +coeff(58)    *x22*x31    *x52
     5  +coeff(59)        *x31*x42*x52
c
      return
      end
****************************************************************************
      function ep24x (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(20)
      data ncoeff/ 19/
      data avdat/  -.4400472E+04/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.14000174E+01,  .16958058E+03, -.65653543E+01,  .14655565E+02,
     +   .96941763E+00,  .72311157E+00,  .87479502E+00, -.81706071E+00,
     +   .16496253E+01,  .10586554E+01,  .31179690E+01,  .13621613E+01,
     +  -.21483658E-01, -.14331393E+00, -.15411828E+00,  .23670287E+00,
     +   .27220100E+00, -.33574682E+00,  .43483767E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep24x =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)*x11                
     4  +coeff( 4)    *x21        *x51
     5  +coeff( 5)                *x51
     6  +coeff( 6)    *x22            
     7  +coeff( 7)*x11            *x51
     8  +coeff( 8)    *x21        *x52
      ep24x =ep24x 
     9  +coeff( 9)    *x23            
     1  +coeff(10)        *x31*x41    
     2  +coeff(11)    *x23*x31*x41    
     3  +coeff(12)    *x23    *x42    
     4  +coeff(13)    *x23*x32*x42    
     5  +coeff(14)*x11*x21            
     6  +coeff(15)*x11*x22            
     7  +coeff(16)        *x32        
     8  +coeff(17)            *x42    
      ep24x =ep24x 
     9  +coeff(18)    *x21    *x42    
     1  +coeff(19)    *x23*x32        
c
      return
      end
****************************************************************************
      function ep24z (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(30)
      data ncoeff/ 29/
      data avdat/   .0000000E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.14720213E+03, -.19075750E+02,  .31434255E+01, -.32509922E+02,
     +   .88199244E+01, -.13392229E+02,  .18213963E+02, -.89160018E-02,
     +   .12349474E+02,  .34904478E+01,  .16559074E+01,  .78661364E+00,
     +   .41452827E+01,  .85912943E+00,  .10422354E+02,  .52513375E+01,
     +   .20877421E+00,  .24222022E+00, -.52469362E-01, -.93890436E-01,
     +   .25627407E+00, -.32027146E+00,  .51392328E-01, -.56271101E-02,
     +  -.15068872E-01,  .14674057E+00,  .35258214E+01,  .36710188E+00,
     +   .36135608E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x33 = 2.*x3*x32 - x31
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep24z =avdat
     1  +coeff( 1)            *x41    
     2  +coeff( 2)        *x31        
     3  +coeff( 3)            *x43    
     4  +coeff( 4)            *x41*x51
     5  +coeff( 5)        *x31*x42    
     6  +coeff( 6)        *x31    *x51
     7  +coeff( 7)    *x22    *x41    
     8  +coeff( 8)    *x21    *x43    
      ep24z =ep24z 
     9  +coeff( 9)    *x22*x31        
     1  +coeff(10)    *x21    *x41    
     2  +coeff(11)            *x41*x52
     3  +coeff(12)    *x21*x31        
     4  +coeff(13)        *x32*x41    
     5  +coeff(14)        *x31    *x52
     6  +coeff(15)    *x22*x31*x42    
     7  +coeff(16)    *x22*x32*x41    
     8  +coeff(17)    *x22*x31*x44    
      ep24z =ep24z 
     9  +coeff(18)    *x22*x32*x43    
     1  +coeff(19)    *x22*x33*x44    
     2  +coeff(20)*x11        *x41    
     3  +coeff(21)        *x33        
     4  +coeff(22)*x11*x21    *x41    
     5  +coeff(23)            *x43*x51
     6  +coeff(24)    *x21*x32*x41    
     7  +coeff(25)        *x32*x43    
     8  +coeff(26)    *x21*x33        
      ep24z =ep24z 
     9  +coeff(27)    *x22    *x43    
     1  +coeff(28)    *x22    *x41*x51
     2  +coeff(29)    *x22*x33        
c
      return
      end
****************************************************************************
      function ep26x (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(58)
      data ncoeff/ 57/
      data avdat/   .4611102E+01/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .17323979E+01,  .39823456E+03, -.19466770E+02,  .18562807E+03,
     +  -.24413993E+01,  .75811089E+02, -.34793024E+01,  .83810049E+00,
     +   .67577891E+01, -.96338230E+00, -.88324761E+00, -.77330446E+00,
     +  -.64226875E+01,  .68559813E+00, -.14172575E+02, -.23420713E+01,
     +  -.10113480E+01, -.38949311E+00, -.69105703E+00, -.83335376E+00,
     +   .62697643E+00, -.30715063E+00,  .32329309E+00,  .28291514E+01,
     +   .16739334E+00,  .80567591E-01,  .31419258E+01,  .44990429E+00,
     +   .11867169E+00,  .36107811E+00,  .32386497E+00,  .11893096E+01,
     +  -.70265390E-01, -.16280912E+00, -.14158992E+00,  .57163806E+01,
     +   .17506825E+01,  .46186534E+00,  .77847338E+00,  .19932564E+00,
     +  -.11940230E+00,  .21630953E+00,  .20814091E+00, -.15834595E+00,
     +  -.62081486E+00, -.61623745E-01, -.32096259E-01,  .62801301E-01,
     +  -.35374366E-01,  .16185639E-01, -.24050182E-01,  .34997050E-01,
     +   .12889677E-01, -.56827117E-01,  .17308772E-01,  .17326938E-01,
     +  -.13453629E-01,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep26x =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)*x11                
     4  +coeff( 4)                *x51
     5  +coeff( 5)            *x42    
     6  +coeff( 6)    *x21        *x51
     7  +coeff( 7)                *x52
     8  +coeff( 8)    *x22    *x42    
      ep26x =ep26x 
     9  +coeff( 9)    *x22            
     1  +coeff(10)    *x21*x31*x43    
     2  +coeff(11)    *x21*x32*x42    
     3  +coeff(12)*x11*x21            
     4  +coeff(13)    *x21    *x42    
     5  +coeff(14)*x11            *x51
     6  +coeff(15)    *x21*x31*x41    
     7  +coeff(16)    *x21*x32        
     8  +coeff(17)    *x21        *x52
      ep26x =ep26x 
     9  +coeff(18)*x11*x22            
     1  +coeff(19)    *x24            
     2  +coeff(20)            *x42*x51
     3  +coeff(21)        *x31*x41    
     4  +coeff(22)    *x22        *x51
     5  +coeff(23)*x11*x21        *x51
     6  +coeff(24)    *x23    *x42    
     7  +coeff(25)        *x32    *x51
     8  +coeff(26)    *x23    *x42*x51
      ep26x =ep26x 
     9  +coeff(27)    *x23            
     1  +coeff(28)        *x32        
     2  +coeff(29)*x11*x23            
     3  +coeff(30)    *x23        *x51
     4  +coeff(31)    *x22*x31*x41    
     5  +coeff(32)    *x21    *x42*x51
     6  +coeff(33)    *x22*x32        
     7  +coeff(34)    *x24        *x51
     8  +coeff(35)    *x22        *x52
      ep26x =ep26x 
     9  +coeff(36)    *x23*x31*x41    
     1  +coeff(37)    *x21*x31*x41*x51
     2  +coeff(38)        *x32*x42    
     3  +coeff(39)    *x23*x32        
     4  +coeff(40)        *x31*x43    
     5  +coeff(41)    *x24    *x42    
     6  +coeff(42)    *x22    *x42*x51
     7  +coeff(43)    *x21*x32    *x51
     8  +coeff(44)    *x24*x32        
      ep26x =ep26x 
     9  +coeff(45)    *x24*x31*x41    
     1  +coeff(46)    *x22*x32    *x51
     2  +coeff(47)        *x32    *x52
     3  +coeff(48)        *x31*x41*x51
     4  +coeff(49)*x11*x21    *x42    
     5  +coeff(50)*x11            *x52
     6  +coeff(51)*x11*x22    *x42    
     7  +coeff(52)*x11*x23        *x51
     8  +coeff(53)    *x23        *x52
      ep26x =ep26x 
     9  +coeff(54)        *x31*x41*x52
     1  +coeff(55)*x11*x22*x32        
     2  +coeff(56)*x11    *x31*x43    
     3  +coeff(57)    *x24        *x52
c
      return
      end
****************************************************************************
      function ep26z (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(59)
      data ncoeff/ 58/
      data avdat/   .0000000E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .99889641E+02, -.65687973E+02,  .18902851E+02,  .59044861E+02,
     +  -.35499794E+02, -.82301758E+02,  .31548656E+02,  .49429569E+02,
     +   .66534896E+01, -.24740846E+01,  .30641172E+01,  .39399378E+01,
     +  -.91682628E-01, -.10208750E+01,  .86723471E+00, -.10269823E+01,
     +   .20857718E+01,  .22643363E+01,  .11447848E+02,  .23537176E+02,
     +   .84446459E+01, -.43359336E-01,  .80950275E-01,  .23581772E+02,
     +   .81617985E+01,  .36858194E-01, -.52307570E+00, -.81829327E+00,
     +   .27558044E+00,  .91623586E+00,  .11598520E+02, -.85680860E+00,
     +   .61083049E+00,  .68266714E+00, -.39307696E+00,  .30467281E+00,
     +  -.46252787E+00, -.47340915E+00,  .63929133E-01, -.48952684E-01,
     +   .29785672E+00,  .16623269E+00,  .36172503E+00,  .33040282E+00,
     +  -.19301555E+00, -.83316430E-01,  .16986483E+00, -.21116599E-01,
     +   .24737224E-01, -.14622729E+01, -.19544452E+01, -.51520264E+00,
     +   .37023831E-01,  .66905484E-01,  .45665190E+00,  .18718471E+00,
     +   .68647444E-01,  .15852843E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x33 = 2.*x3*x32 - x31
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep26z =avdat
     1  +coeff( 1)        *x31        
     2  +coeff( 2)            *x41    
     3  +coeff( 3)    *x21*x31        
     4  +coeff( 4)    *x21    *x41    
     5  +coeff( 5)        *x31    *x51
     6  +coeff( 6)            *x41*x51
     7  +coeff( 7)    *x22*x31        
     8  +coeff( 8)    *x22    *x41    
      ep26z =ep26z 
     9  +coeff( 9)    *x21    *x41*x51
     1  +coeff(10)*x11        *x41    
     2  +coeff(11)    *x21*x31    *x51
     3  +coeff(12)            *x41*x52
     4  +coeff(13)        *x31*x42*x52
     5  +coeff(14)*x11    *x31        
     6  +coeff(15)        *x33        
     7  +coeff(16)*x11*x21    *x41    
     8  +coeff(17)        *x31    *x52
      ep26z =ep26z 
     9  +coeff(18)    *x22    *x41*x51
     1  +coeff(19)        *x32*x41    
     2  +coeff(20)        *x31*x42    
     3  +coeff(21)            *x43    
     4  +coeff(22)*x11*x21*x31        
     5  +coeff(23)    *x21*x33        
     6  +coeff(24)    *x22*x31*x42    
     7  +coeff(25)    *x22    *x43    
     8  +coeff(26)        *x32*x43    
      ep26z =ep26z 
     9  +coeff(27)    *x23*x31        
     1  +coeff(28)    *x23    *x41    
     2  +coeff(29)*x11        *x41*x51
     3  +coeff(30)    *x22*x33        
     4  +coeff(31)    *x22*x32*x41    
     5  +coeff(32)    *x21    *x41*x52
     6  +coeff(33)*x11*x23    *x41    
     7  +coeff(34)    *x22*x31    *x51
     8  +coeff(35)    *x21*x31    *x52
      ep26z =ep26z 
     9  +coeff(36)*x11*x23*x31        
     1  +coeff(37)    *x23    *x41*x51
     2  +coeff(38)    *x23*x32*x41    
     3  +coeff(39)*x11    *x31    *x51
     4  +coeff(40)*x11    *x32*x41    
     5  +coeff(41)            *x43*x51
     6  +coeff(42)        *x33*x42    
     7  +coeff(43)*x11*x21    *x41*x51
     8  +coeff(44)*x11*x21*x32*x41    
      ep26z =ep26z 
     9  +coeff(45)    *x23*x31    *x51
     1  +coeff(46)    *x23*x33        
     2  +coeff(47)    *x23    *x43    
     3  +coeff(48)    *x21*x32*x43    
     4  +coeff(49)*x12        *x41    
     5  +coeff(50)    *x21*x32*x41    
     6  +coeff(51)    *x21*x31*x42    
     7  +coeff(52)    *x21    *x43    
     8  +coeff(53)*x11*x22    *x41    
      ep26z =ep26z 
     9  +coeff(54)        *x32*x41*x51
     1  +coeff(55)        *x31*x42*x51
     2  +coeff(56)*x11*x21*x31    *x51
     3  +coeff(57)*x11*x21*x33        
     4  +coeff(58)*x11*x21*x31*x42    
c
      return
      end
****************************************************************************
      function ep29  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(60)
      data ncoeff/ 59/
      data avdat/   .8296787E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +  -.11476194E+00,  .18083452E+00,  .24616204E+00, -.43227472E-02,
     +   .37633774E+00,  .40117368E-01,  .10336453E+01,  .25451431E+00,
     +  -.76870888E-01,  .48095852E-01, -.23302388E+00, -.79863057E-01,
     +  -.58932323E-01,  .19539526E+00,  .84391296E-01,  .95238425E-01,
     +  -.76070949E-02,  .50087739E-01, -.24134012E-01, -.13857654E-01,
     +  -.22963375E-01,  .28137421E-01, -.12014071E+00,  .25757402E-01,
     +  -.53134285E-01, -.14641729E+00,  .57445388E-01, -.45179170E-01,
     +  -.28911929E-02,  .13076133E+00, -.10838217E-01, -.16433780E+00,
     +   .11328611E-01,  .23379721E-01,  .83809486E-02,  .42551165E-02,
     +   .20478962E-02, -.12540779E-02,  .15071812E-01, -.24058025E-01,
     +  -.14753855E-01,  .23405817E-02, -.15381454E-01, -.46220343E-02,
     +  -.58033940E-03,  .10149198E-02,  .42853719E-02,  .39978744E-02,
     +  -.22063549E-02, -.34117165E-02,  .46047247E-02,  .14379887E-01,
     +   .41517289E-02, -.79894001E-02,  .12057424E-01, -.62875240E-02,
     +   .15269717E-01,  .47620810E-02, -.12274433E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
      x53 = 2.*x5*x52 - x51
c
c                  function
c
      ep29  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)                *x51
     4  +coeff( 4)*x11                
     5  +coeff( 5)    *x22            
     6  +coeff( 6)            *x42    
     7  +coeff( 7)    *x21        *x51
     8  +coeff( 8)                *x52
      ep29  =ep29  
     9  +coeff( 9)*x11*x21            
     1  +coeff(10)    *x23            
     2  +coeff(11)        *x31*x41    
     3  +coeff(12)    *x21    *x42    
     4  +coeff(13)*x11            *x51
     5  +coeff(14)    *x22        *x51
     6  +coeff(15)            *x42*x51
     7  +coeff(16)    *x21        *x52
     8  +coeff(17)*x11*x22            
      ep29  =ep29  
     9  +coeff(18)        *x32        
     1  +coeff(19)    *x22    *x42    
     2  +coeff(20)                *x53
     3  +coeff(21)*x11*x21        *x51
     4  +coeff(22)    *x23        *x51
     5  +coeff(23)    *x21    *x42*x51
     6  +coeff(24)    *x21*x32        
     7  +coeff(25)        *x32    *x51
     8  +coeff(26)    *x21*x31*x41*x51
      ep29  =ep29  
     9  +coeff(27)        *x31*x41*x52
     1  +coeff(28)    *x22*x31*x41*x51
     2  +coeff(29)        *x31*x43*x51
     3  +coeff(30)    *x21*x31*x41    
     4  +coeff(31)            *x44    
     5  +coeff(32)        *x31*x41*x51
     6  +coeff(33)    *x22        *x52
     7  +coeff(34)            *x42*x52
     8  +coeff(35)        *x32    *x52
      ep29  =ep29  
     9  +coeff(36)*x11        *x42    
     1  +coeff(37)*x11            *x52
     2  +coeff(38)*x11*x23            
     3  +coeff(39)    *x23    *x42    
     4  +coeff(40)        *x31*x43    
     5  +coeff(41)    *x22    *x42*x51
     6  +coeff(42)    *x23        *x52
     7  +coeff(43)    *x21*x32    *x51
     8  +coeff(44)    *x22*x32    *x51
      ep29  =ep29  
     9  +coeff(45)    *x24    *x44    
     1  +coeff(46)*x12                
     2  +coeff(47)    *x24            
     3  +coeff(48)*x11*x21    *x42    
     4  +coeff(49)    *x21        *x53
     5  +coeff(50)*x11*x22        *x51
     6  +coeff(51)    *x22*x32        
     7  +coeff(52)    *x23*x31*x41    
     8  +coeff(53)    *x24    *x42    
      ep29  =ep29  
     9  +coeff(54)        *x32*x42    
     1  +coeff(55)    *x23    *x42*x51
     2  +coeff(56)    *x22*x31*x43    
     3  +coeff(57)    *x23*x31*x41*x51
     4  +coeff(58)    *x22    *x44*x51
     5  +coeff(59)    *x24*x32        
c
      return
      end
****************************************************************************
      function ep32  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(60)
      data ncoeff/ 59/
      data avdat/   .6383948E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .49448490E-01,  .13218404E+00,  .11370596E+00, -.34052220E-02,
     +   .12533019E+00,  .79692177E-01,  .66515523E+00,  .44001484E+00,
     +  -.31006809E-01,  .25331127E-01, -.17603828E+00, -.80659196E-01,
     +  -.50623808E-01,  .83601855E-01,  .92985593E-01,  .11565730E+00,
     +  -.27957974E-01,  .95551103E-01,  .17623867E+00, -.18653810E-01,
     +   .16146420E-01, -.27544543E+00, -.16355748E+00,  .38137048E-01,
     +   .39437909E-01, -.66900194E-01, -.21316627E+00,  .74562594E-01,
     +  -.19855782E-01,  .10439627E-01,  .40477766E-02,  .14330824E-02,
     +  -.13268835E-01,  .10289458E-01,  .18003783E-02,  .70992954E-01,
     +   .12697198E-01, -.33377994E-01,  .16069071E-01, -.39389502E-01,
     +  -.55775014E-02,  .99075213E-03, -.38668436E-02, -.68212301E-02,
     +  -.10444549E-01, -.20054413E-02, -.96633146E-02, -.31369240E-02,
     +   .49658259E-03, -.45077121E-02, -.21897270E-02,  .43199654E-02,
     +   .23436889E-02, -.22021863E-02,  .34795529E-02, -.28512909E-02,
     +   .76514496E-02,  .68409382E-02, -.57656979E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
      x53 = 2.*x5*x52 - x51
      x54 = 2.*x5*x53 - x52
c
c                  function
c
      ep32  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)                *x51
     4  +coeff( 4)*x11                
     5  +coeff( 5)    *x22            
     6  +coeff( 6)            *x42    
     7  +coeff( 7)    *x21        *x51
     8  +coeff( 8)                *x52
      ep32  =ep32  
     9  +coeff( 9)*x11*x21            
     1  +coeff(10)    *x23            
     2  +coeff(11)        *x31*x41    
     3  +coeff(12)    *x21    *x42    
     4  +coeff(13)*x11            *x51
     5  +coeff(14)    *x22        *x51
     6  +coeff(15)            *x42*x51
     7  +coeff(16)    *x21        *x52
     8  +coeff(17)                *x53
      ep32  =ep32  
     9  +coeff(18)        *x32        
     1  +coeff(19)    *x21*x31*x41    
     2  +coeff(20)    *x22    *x42    
     3  +coeff(21)    *x23        *x51
     4  +coeff(22)        *x31*x41*x51
     5  +coeff(23)    *x21    *x42*x51
     6  +coeff(24)            *x42*x52
     7  +coeff(25)    *x21*x32        
     8  +coeff(26)        *x32    *x51
      ep32  =ep32  
     9  +coeff(27)    *x21*x31*x41*x51
     1  +coeff(28)        *x31*x41*x52
     2  +coeff(29)    *x21*x32    *x51
     3  +coeff(30)        *x32    *x52
     4  +coeff(31)    *x24            
     5  +coeff(32)*x11        *x42    
     6  +coeff(33)*x11*x21        *x51
     7  +coeff(34)    *x22        *x52
     8  +coeff(35)                *x54
      ep32  =ep32  
     9  +coeff(36)    *x22*x31*x41    
     1  +coeff(37)    *x23    *x42    
     2  +coeff(38)    *x22    *x42*x51
     3  +coeff(39)    *x22*x32        
     4  +coeff(40)    *x22*x31*x41*x51
     5  +coeff(41)            *x44    
     6  +coeff(42)*x11            *x52
     7  +coeff(43)    *x21        *x53
     8  +coeff(44)*x11    *x31*x41    
      ep32  =ep32  
     9  +coeff(45)        *x31*x43    
     1  +coeff(46)*x11    *x32        
     2  +coeff(47)*x11*x21*x31*x41    
     3  +coeff(48)    *x23*x31*x43    
     4  +coeff(49)*x12                
     5  +coeff(50)*x11*x22            
     6  +coeff(51)*x11*x22        *x51
     7  +coeff(52)*x11        *x42*x51
     8  +coeff(53)    *x23        *x52
      ep32  =ep32  
     9  +coeff(54)*x11*x22    *x42    
     1  +coeff(55)    *x24    *x42    
     2  +coeff(56)    *x22    *x44    
     3  +coeff(57)*x11    *x31*x41*x51
     4  +coeff(58)    *x23    *x42*x51
     5  +coeff(59)        *x31*x43*x51
c
      return
      end
****************************************************************************
      function ep34  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(54)
      data ncoeff/ 53/
      data avdat/   .9116645E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.52500E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .39999433E-01,  .29244959E+00,  .45940545E+00, -.14439038E-01,
     +   .62113233E-01,  .66472280E+00,  .78256762E+00, -.18064288E-01,
     +   .17840609E-01, -.75881511E-01,  .83175384E-01,  .16692823E+00,
     +  -.59383385E-01,  .54510865E-01, -.10136224E+00,  .29151408E-01,
     +   .26669424E-01,  .11366262E+00, -.29529573E-01, -.19356328E+00,
     +  -.23379405E-02, -.10107447E+00,  .25492530E-01,  .11920482E-01,
     +   .42354614E-01,  .19924903E-01, -.28588704E-02,  .47555935E-01,
     +  -.78117615E-02,  .86761406E-02, -.76123090E-02,  .45582857E-02,
     +  -.43542411E-01,  .39229851E-01,  .38226251E-01, -.87904772E-02,
     +  -.98225564E-01,  .25504598E-01, -.24693294E-02, -.46360651E-02,
     +   .21303928E-01,  .88179088E-03, -.22612240E-02, -.12875228E-02,
     +   .64568343E-02, -.25813722E-02,  .10707557E-02,  .29316817E-02,
     +   .46274583E-02, -.61387080E-02,  .36340025E-02,  .47950234E-03,
     +  -.12574916E-02,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x51 = x5
      x52 = 2.*x5*x51 -1.
      x53 = 2.*x5*x52 - x51
      x54 = 2.*x5*x53 - x52
c
c                  function
c
      ep34  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)                *x51
     4  +coeff( 4)*x11                
     5  +coeff( 5)    *x22            
     6  +coeff( 6)    *x21        *x51
     7  +coeff( 7)                *x52
     8  +coeff( 8)*x11*x21            
      ep34  =ep34  
     9  +coeff( 9)    *x23            
     1  +coeff(10)*x11            *x51
     2  +coeff(11)    *x22        *x51
     3  +coeff(12)    *x21        *x52
     4  +coeff(13)                *x53
     5  +coeff(14)        *x32        
     6  +coeff(15)        *x31*x41    
     7  +coeff(16)    *x23        *x51
     8  +coeff(17)    *x21*x32        
      ep34  =ep34  
     9  +coeff(18)    *x21*x31*x41    
     1  +coeff(19)        *x32    *x51
     2  +coeff(20)        *x31*x41*x51
     3  +coeff(21)    *x22    *x42    
     4  +coeff(22)    *x21    *x42*x51
     5  +coeff(23)        *x31*x41*x52
     6  +coeff(24)    *x23    *x42    
     7  +coeff(25)    *x23*x31*x41*x51
     8  +coeff(26)    *x23    *x42*x51
      ep34  =ep34  
     9  +coeff(27)    *x24            
     1  +coeff(28)            *x42    
     2  +coeff(29)*x11*x21        *x51
     3  +coeff(30)    *x22        *x52
     4  +coeff(31)    *x21        *x53
     5  +coeff(32)                *x54
     6  +coeff(33)    *x21    *x42    
     7  +coeff(34)            *x42*x51
     8  +coeff(35)    *x22*x31*x41    
      ep34  =ep34  
     9  +coeff(36)    *x21*x32    *x51
     1  +coeff(37)    *x21*x31*x41*x51
     2  +coeff(38)            *x42*x52
     3  +coeff(39)    *x24*x32        
     4  +coeff(40)    *x24        *x51
     5  +coeff(41)    *x23*x31*x41    
     6  +coeff(42)*x11            *x52
     7  +coeff(43)*x11*x22        *x51
     8  +coeff(44)*x11    *x32        
      ep34  =ep34  
     9  +coeff(45)    *x22*x32        
     1  +coeff(46)*x11    *x31*x41    
     2  +coeff(47)*x11*x23        *x51
     3  +coeff(48)        *x32    *x52
     4  +coeff(49)*x11    *x31*x41*x51
     5  +coeff(50)    *x24*x31*x41    
     6  +coeff(51)    *x23*x32    *x51
     7  +coeff(52)*x12                
     8  +coeff(53)*x11*x22            
c
      return
      end
****************************************************************************
      function ep37x  (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(56)
      data ncoeff/ 55/
      data avdat/  -.4015480E+02/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.52500E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .17190959E+03, -.29425404E+02,  .21305368E+01, -.10554954E+02,
     +  -.32196426E+01,  .72418909E+03,  .28677002E+02, -.22196655E+02,
     +   .76984925E+01, -.42630774E+00,  .26878159E+01,  .22437606E+01,
     +  -.33317466E+01, -.25115724E+01, -.13905260E+02,  .28420813E+01,
     +  -.14321810E+02,  .37640347E+01, -.18764528E+01, -.64156051E+01,
     +  -.38125196E+00,  .45057595E+00, -.12003886E+02, -.19263828E+01,
     +  -.50736380E+01, -.48529837E+00, -.16289821E+00,  .29164934E+01,
     +   .36154237E+01,  .40222225E+01, -.16843148E+01,  .10181006E+01,
     +  -.72614412E+01,  .47329018E+00,  .11906793E+01, -.59746366E+01,
     +   .35575435E+00, -.17318449E+01, -.55115504E+01, -.18834113E+00,
     +   .51369059E+00, -.51197225E+00,  .36031717E+00, -.98548585E+00,
     +   .99159427E-01, -.54324925E+00,  .10115801E+01, -.86654967E+00,
     +  -.17497821E+01,  .12529422E+01, -.14695778E+01, -.32781243E+00,
     +   .89179307E+00,  .25093126E+01, -.64788431E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x25 = 2.*x2*x24 - x23
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x44 = 2.*x4*x43 - x42
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep37x  =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)    *x22            
     4  +coeff( 4)*x11                
     5  +coeff( 5)            *x42    
     6  +coeff( 6)                *x51
     7  +coeff( 7)    *x21        *x51
     8  +coeff( 8)        *x31*x41    
      ep37x  =ep37x  
     9  +coeff( 9)                *x52
     1  +coeff(10)    *x21    *x44    
     2  +coeff(11)    *x23            
     3  +coeff(12)*x11*x21            
     4  +coeff(13)    *x24            
     5  +coeff(14)*x11            *x51
     6  +coeff(15)    *x21    *x42    
     7  +coeff(16)    *x22    *x42    
     8  +coeff(17)    *x21*x31*x41    
      ep37x  =ep37x  
     9  +coeff(18)            *x42*x51
     1  +coeff(19)    *x21*x32        
     2  +coeff(20)    *x21    *x42*x51
     3  +coeff(21)*x11*x22            
     4  +coeff(22)*x11*x23            
     5  +coeff(23)        *x31*x41*x51
     6  +coeff(24)    *x24        *x51
     7  +coeff(25)    *x21*x31*x41*x51
     8  +coeff(26)    *x21    *x42*x52
      ep37x  =ep37x  
     9  +coeff(27)    *x25            
     1  +coeff(28)    *x23    *x42    
     2  +coeff(29)    *x23*x31*x41    
     3  +coeff(30)    *x22    *x42*x51
     4  +coeff(31)    *x24*x31*x41    
     5  +coeff(32)    *x23*x32        
     6  +coeff(33)    *x22*x31*x41*x51
     7  +coeff(34)    *x23*x31*x41*x51
     8  +coeff(35)    *x22*x32    *x51
      ep37x  =ep37x  
     9  +coeff(36)    *x21*x31*x41*x52
     1  +coeff(37)*x11        *x42    
     2  +coeff(38)    *x23        *x51
     3  +coeff(39)    *x22*x31*x41    
     4  +coeff(40)*x11*x21    *x42    
     5  +coeff(41)*x11*x21        *x51
     6  +coeff(42)    *x21        *x52
     7  +coeff(43)*x11    *x31*x41    
     8  +coeff(44)    *x24    *x42    
      ep37x  =ep37x  
     9  +coeff(45)    *x22*x32        
     1  +coeff(46)    *x22        *x52
     2  +coeff(47)            *x42*x52
     3  +coeff(48)    *x23        *x52
     4  +coeff(49)    *x21*x32*x42    
     5  +coeff(50)    *x21*x32    *x51
     6  +coeff(51)        *x31*x41*x52
     7  +coeff(52)    *x24*x32        
     8  +coeff(53)    *x22    *x42*x52
      ep37x  =ep37x  
     9  +coeff(54)    *x21*x31*x43*x51
     1  +coeff(55)        *x32*x42*x51
c
      return
      end
****************************************************************************
      function ep37z (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(61)
      data ncoeff/ 60/
      data avdat/   .0000000E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.52500E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .60534935E+02,  .40540691E+02,  .24571049E+01,  .11696986E+02,
     +   .42584262E+01,  .68999124E+01, -.38320043E+01, -.11695715E+02,
     +   .24412851E+01,  .21046033E+01,  .21312065E+01,  .34819608E+01,
     +  -.51494783E+00, -.13625364E+01,  .29408824E+01,  .14207020E+01,
     +  -.66891235E+00,  .16363438E+01, -.21526420E+00, -.49176881E+00,
     +  -.21277177E+01, -.28742167E+00,  .94570518E+00, -.19912112E+01,
     +  -.23791447E+01,  .20382438E+01,  .25377524E+00,  .32771549E+00,
     +  -.80547845E+00, -.32573022E-01,  .55874139E+00, -.20092481E+00,
     +   .89212781E+00, -.18651923E+01,  .65345210E+00,  .21242564E+01,
     +   .97639507E+00, -.73237360E+00,  .16552825E+01, -.13663073E+01,
     +  -.22695494E+00, -.41017580E+00, -.89968628E+00, -.38737696E+00,
     +  -.54864633E+00, -.18989459E+00, -.58122385E+00, -.61529696E+00,
     +  -.84270984E-01,  .71649116E+00,  .17087111E+00, -.29087355E+01,
     +  -.15426378E+00,  .13344494E+00, -.98205581E-01,  .24735306E+00,
     +   .59359401E+00, -.21458367E+00, -.80249429E-01,  .78665709E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x33 = 2.*x3*x32 - x31
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x51 = x5
      x52 = 2.*x5*x51 -1.
      x53 = 2.*x5*x52 - x51
c
c                  function
c
      ep37z =avdat
     1  +coeff( 1)            *x41    
     2  +coeff( 2)        *x31        
     3  +coeff( 3)    *x21    *x41    
     4  +coeff( 4)    *x21*x31        
     5  +coeff( 5)            *x41*x51
     6  +coeff( 6)    *x22    *x41    
     7  +coeff( 7)        *x31    *x51
     8  +coeff( 8)    *x21    *x41*x51
      ep37z =ep37z 
     9  +coeff( 9)    *x21*x31    *x51
     1  +coeff(10)            *x41*x52
     2  +coeff(11)        *x31    *x52
     3  +coeff(12)    *x22*x31        
     4  +coeff(13)*x11        *x41    
     5  +coeff(14)    *x23    *x41    
     6  +coeff(15)        *x32*x41    
     7  +coeff(16)    *x21*x31*x42    
     8  +coeff(17)    *x24    *x41    
      ep37z =ep37z 
     9  +coeff(18)            *x43    
     1  +coeff(19)*x11    *x31        
     2  +coeff(20)*x11*x21    *x41    
     3  +coeff(21)    *x22    *x41*x51
     4  +coeff(22)        *x33        
     5  +coeff(23)            *x43*x51
     6  +coeff(24)    *x23    *x41*x51
     7  +coeff(25)    *x22    *x41*x52
     8  +coeff(26)    *x21*x32*x41*x51
      ep37z =ep37z 
     9  +coeff(27)    *x21    *x43*x52
     1  +coeff(28)    *x22*x32*x41*x51
     2  +coeff(29)    *x22*x31    *x53
     3  +coeff(30)    *x23*x31*x42*x51
     4  +coeff(31)        *x31*x42    
     5  +coeff(32)    *x24*x31        
     6  +coeff(33)    *x22    *x43    
     7  +coeff(34)        *x31*x42*x51
     8  +coeff(35)    *x21*x31    *x52
      ep37z =ep37z 
     9  +coeff(36)    *x22*x31*x42    
     1  +coeff(37)        *x32*x41*x51
     2  +coeff(38)            *x41*x53
     3  +coeff(39)    *x22*x32*x41    
     4  +coeff(40)    *x21    *x41*x53
     5  +coeff(41)    *x23    *x41*x52
     6  +coeff(42)    *x21*x33    *x51
     7  +coeff(43)    *x23*x31    *x52
     8  +coeff(44)    *x21*x32*x43    
      ep37z =ep37z 
     9  +coeff(45)    *x24*x31    *x52
     1  +coeff(46)        *x32*x41*x53
     2  +coeff(47)    *x23*x31    *x53
     3  +coeff(48)    *x21*x32*x43*x51
     4  +coeff(49)*x11*x21*x31        
     5  +coeff(50)    *x22*x31    *x51
     6  +coeff(51)*x11        *x41*x51
     7  +coeff(52)    *x21    *x41*x52
     8  +coeff(53)    *x21*x33        
      ep37z =ep37z 
     9  +coeff(54)*x11*x23    *x41    
     1  +coeff(55)    *x22*x33        
     2  +coeff(56)    *x22*x31    *x52
     3  +coeff(57)            *x43*x52
     4  +coeff(58)    *x24*x31    *x51
     5  +coeff(59)*x11*x24    *x41    
     6  +coeff(60)        *x32*x41*x52
c
      return
      end
****************************************************************************
      function ep38x (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(53)
      data ncoeff/ 52/
      data avdat/   .5971336E+01/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.52500E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .13656015E+03, -.44376629E+02,  .28502393E+01,  .78311310E+03,
     +   .27713524E+02, -.37437993E+00,  .37764403E+00, -.10715003E+02,
     +  -.18978971E+02, -.99320574E+01,  .78472252E+01,  .31394849E+01,
     +  -.21079428E+01,  .25631669E+01, -.29337101E+01, -.25916760E+01,
     +  -.58239489E+01,  .38441417E+01,  .57956028E+01, -.10371588E+00,
     +  -.49085259E+01, -.21143148E+01, -.75425696E+01, -.13517699E+01,
     +   .22477117E+01, -.18553774E+00,  .53003711E+00,  .71923149E+00,
     +   .33957624E+01,  .58904057E+01,  .45424757E+01,  .11482714E+01,
     +   .14821837E+01,  .16501495E+01, -.29969850E+01,  .38349848E-01,
     +   .34209807E+01, -.19034224E+01,  .12745515E+01,  .14960418E-01,
     +   .70977020E+00, -.14181913E+01, -.58583385E+00,  .69156784E+00,
     +  -.69547725E+00, -.89000806E-01,  .13508147E+01, -.36825567E+00,
     +  -.51586278E-01,  .40157935E+00,  .39449382E+00, -.30758673E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x12 = 2.*x1*x11 -1.
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x25 = 2.*x2*x24 - x23
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep38x =avdat
     1  +coeff( 1)                    
     2  +coeff( 2)    *x21            
     3  +coeff( 3)    *x22            
     4  +coeff( 4)                *x51
     5  +coeff( 5)    *x21        *x51
     6  +coeff( 6)*x11*x22            
     7  +coeff( 7)*x11        *x42    
     8  +coeff( 8)*x11                
      ep38x =ep38x 
     9  +coeff( 9)        *x31*x41    
     1  +coeff(10)    *x21    *x42    
     2  +coeff(11)                *x52
     3  +coeff(12)    *x23            
     4  +coeff(13)            *x42    
     5  +coeff(14)*x11*x21            
     6  +coeff(15)    *x24            
     7  +coeff(16)*x11            *x51
     8  +coeff(17)    *x21*x31*x41    
      ep38x =ep38x 
     9  +coeff(18)    *x22    *x42    
     1  +coeff(19)            *x42*x51
     2  +coeff(20)    *x21*x32        
     3  +coeff(21)    *x21    *x42*x51
     4  +coeff(22)    *x24        *x51
     5  +coeff(23)        *x31*x41*x51
     6  +coeff(24)    *x21*x31*x41*x51
     7  +coeff(25)    *x21    *x42*x52
     8  +coeff(26)    *x25            
      ep38x =ep38x 
     9  +coeff(27)*x11*x23            
     1  +coeff(28)*x11*x21        *x51
     2  +coeff(29)    *x23    *x42    
     3  +coeff(30)    *x23*x31*x41    
     4  +coeff(31)    *x22    *x42*x51
     5  +coeff(32)    *x23*x32        
     6  +coeff(33)            *x42*x52
     7  +coeff(34)    *x21*x32    *x51
     8  +coeff(35)    *x22*x31*x41*x51
      ep38x =ep38x 
     9  +coeff(36)    *x24        *x52
     1  +coeff(37)    *x23*x31*x41*x51
     2  +coeff(38)    *x23        *x51
     3  +coeff(39)    *x21        *x52
     4  +coeff(40)    *x22*x31*x41    
     5  +coeff(41)    *x22*x32        
     6  +coeff(42)    *x22        *x52
     7  +coeff(43)    *x24    *x42    
     8  +coeff(44)        *x32    *x51
      ep38x =ep38x 
     9  +coeff(45)    *x23        *x52
     1  +coeff(46)    *x24*x32        
     2  +coeff(47)    *x22*x32    *x51
     3  +coeff(48)    *x22        *x51
     4  +coeff(49)*x12                
     5  +coeff(50)        *x32        
     6  +coeff(51)*x11    *x31*x41    
     7  +coeff(52)*x11*x21    *x42    
c
      return
      end
****************************************************************************
      function ep38z (x,m)
      dimension x(m)
      dimension xmin(10),xmax(10),scale(10)
      dimension coeff(53)
      data ncoeff/ 52/
      data avdat/   .0000000E+00/
      data xmin/
     1  -.50000E+01, -.70000E-01, -.60000E+02, -.40071E-01, -.52500E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data xmax/
     1   .50000E+01,  .70000E-01,  .60000E+02,  .40071E-01,  .70000E-01,
     2   .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00,  .00000E+00/
      data scale /10*0./
      data coeff/
     +   .25276869E+02,  .75353745E+02,  .90486059E+01, -.52087126E+01,
     +  -.90686536E+00,  .24368751E+01,  .16748724E+02, -.92686872E+01,
     +   .12899773E+01, -.20578454E+01, -.11724818E+01, -.65843707E+00,
     +  -.12031384E+01, -.82883102E+00, -.18173082E+00, -.62224996E+00,
     +   .10118504E+01, -.42180176E+01, -.39256403E+00,  .15698048E+01,
     +  -.23144801E+00, -.37484097E+01,  .37046041E+01, -.10736383E+00,
     +  -.14774783E+00, -.45534647E+00,  .10847358E+01, -.26058286E+00,
     +   .35452601E+00,  .76825482E+00, -.15724963E+01, -.80209041E+00,
     +  -.11372081E+01,  .46882026E-01,  .35522166E+00,  .34208778E+00,
     +  -.15909122E+01, -.34098488E+00,  .30670461E+00, -.17165901E+00,
     +  -.23837910E+01, -.43139046E+00,  .84503603E+00,  .25609970E+00,
     +   .13194442E+01, -.61115158E+00, -.11963253E+01,  .13770907E+00,
     +  -.25069946E-01,  .51319045E+00,  .58630002E+00,  .13119963E+00,
     +      0.      /
      data ientry/0/
c
      if (ientry.ne.0) go to 10
      ientry=1
      do 5 i=1,m
      if (xmin(i).eq.xmax(i)) go to 5
      scale(i)=2./(xmax(i)-xmin(i))
   5  continue
c
  10  continue
c      normalize variables between -1 and +1
      x1 =1.+(x( 1)-xmax( 1))*scale( 1)
      x2 =1.+(x( 2)-xmax( 2))*scale( 2)
      x3 =1.+(x( 3)-xmax( 3))*scale( 3)
      x4 =1.+(x( 4)-xmax( 4))*scale( 4)
      x5 =1.+(x( 5)-xmax( 5))*scale( 5)
c          set up chebyshev   functions
      x11 = x1
      x21 = x2
      x22 = 2.*x2*x21 -1.
      x23 = 2.*x2*x22 - x21
      x24 = 2.*x2*x23 - x22
      x31 = x3
      x32 = 2.*x3*x31 -1.
      x33 = 2.*x3*x32 - x31
      x41 = x4
      x42 = 2.*x4*x41 -1.
      x43 = 2.*x4*x42 - x41
      x51 = x5
      x52 = 2.*x5*x51 -1.
c
c                  function
c
      ep38z =avdat
     1  +coeff( 1)        *x31        
     2  +coeff( 2)            *x41    
     3  +coeff( 3)    *x21*x31        
     4  +coeff( 4)    *x21    *x41    
     5  +coeff( 5)    *x22*x31        
     6  +coeff( 6)    *x22    *x41    
     7  +coeff( 7)            *x41*x51
     8  +coeff( 8)    *x21    *x41*x51
      ep38z =ep38z 
     9  +coeff( 9)            *x41*x52
     1  +coeff(10)    *x21*x31*x42*x51
     2  +coeff(11)        *x31    *x51
     3  +coeff(12)    *x23    *x41    
     4  +coeff(13)    *x21*x31    *x51
     5  +coeff(14)        *x31    *x52
     6  +coeff(15)        *x32*x43    
     7  +coeff(16)        *x33        
     8  +coeff(17)        *x32*x41    
      ep38z =ep38z 
     9  +coeff(18)        *x31*x42    
     1  +coeff(19)*x11*x21    *x41    
     2  +coeff(20)    *x21*x31*x42    
     3  +coeff(21)        *x33    *x51
     4  +coeff(22)        *x31*x42*x51
     5  +coeff(23)    *x21*x32*x41*x51
     6  +coeff(24)*x11    *x31        
     7  +coeff(25)*x11        *x41    
     8  +coeff(26)    *x21*x33        
      ep38z =ep38z 
     9  +coeff(27)    *x21*x32*x41    
     1  +coeff(28)    *x22*x33        
     2  +coeff(29)    *x22*x32*x41    
     3  +coeff(30)    *x23*x31    *x51
     4  +coeff(31)    *x23    *x41*x51
     5  +coeff(32)    *x21*x33    *x51
     6  +coeff(33)    *x21    *x41*x52
     7  +coeff(34)    *x24*x31    *x51
     8  +coeff(35)    *x24    *x41*x51
      ep38z =ep38z 
     9  +coeff(36)    *x22*x32*x41*x51
     1  +coeff(37)    *x22    *x41*x52
     2  +coeff(38)        *x33    *x52
     3  +coeff(39)        *x32*x41*x52
     4  +coeff(40)    *x23*x31    *x52
     5  +coeff(41)        *x31*x42*x52
     6  +coeff(42)        *x32*x43*x51
     7  +coeff(43)    *x23*x31        
     8  +coeff(44)    *x24*x31        
      ep38z =ep38z 
     9  +coeff(45)    *x22*x31    *x51
     1  +coeff(46)    *x22    *x41*x51
     2  +coeff(47)    *x22*x31*x42    
     3  +coeff(48)*x11        *x41*x51
     4  +coeff(49)    *x23*x33        
     5  +coeff(50)    *x21*x31    *x52
     6  +coeff(51)    *x23*x31*x42    
     7  +coeff(52)    *x24*x32*x41    
c
      return
      end

****************************************************************************
