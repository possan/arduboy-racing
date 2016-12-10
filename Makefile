all: levelimages.h playerimages.h playerimages2.h titleimages.h

titleimages.h: convert.py title.png startwhite.png startblack.png
	python convert.py title.png startwhite.png startblack.png >titleimages.h

levelimages.h: convert.py groundtile.png groundH.png groundV.png groundC1.png groundC2.png groundC3.png groundC4.png groundD1.png groundD2.png groundD3.png
	python convert.py groundtile.png groundH.png groundV.png groundC1.png groundC2.png groundC3.png groundC4.png groundD1.png groundD2.png groundD3.png >levelimages.h

playerimages.h: car1.png car2.png car3.png car1n.png car1s.png car1e.png car1w.png car1nw.png car1ne.png car1sw.png car1se.png
	python convert.py car1.png car2.png car3.png car1n.png car1s.png car1e.png car1w.png car1nw.png car1ne.png car1sw.png car1se.png >playerimages.h

playerimages2.h: car00.png car01.png car02.png car03.png car04.png car05.png car06.png car07.png car08.png car09.png car10.png car11.png car12.png car13.png car14.png car15.png car16.png car17.png car18.png
	python convert.py car00.png car01.png car02.png car03.png car04.png car05.png car06.png car07.png car08.png car09.png car10.png car11.png car12.png car13.png car14.png car15.png car16.png car17.png car18.png >playerimages2.h
