(function (cjs, an) {

var p; // shortcut to reference prototypes
var lib={};var ss={};var img={};
lib.ssMetadata = [];


(lib.AnMovieClip = function(){
	this.actionFrames = [];
	this.ignorePause = false;
	this.gotoAndPlay = function(positionOrLabel){
		cjs.MovieClip.prototype.gotoAndPlay.call(this,positionOrLabel);
	}
	this.play = function(){
		cjs.MovieClip.prototype.play.call(this);
	}
	this.gotoAndStop = function(positionOrLabel){
		cjs.MovieClip.prototype.gotoAndStop.call(this,positionOrLabel);
	}
	this.stop = function(){
		cjs.MovieClip.prototype.stop.call(this);
	}
}).prototype = p = new cjs.MovieClip();
// symbols:



(lib.Символ1 = function(mode,startPosition,loop,reversed) {
if (loop == null) { loop = true; }
if (reversed == null) { reversed = false; }
	var props = new Object();
	props.mode = mode;
	props.startPosition = startPosition;
	props.labels = {};
	props.loop = loop;
	props.reversed = reversed;
	cjs.MovieClip.apply(this,[props]);

	// Слой_1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("rgba(0,51,204,0.098)").s().p("EgjJAKeIAA07MBGTAAAIAAU7g");
	this.shape.setTransform(5,1.025);

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(4));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-220,-65.9,450,133.9);


(lib.Анимация4 = function(mode,startPosition,loop,reversed) {
if (loop == null) { loop = true; }
if (reversed == null) { reversed = false; }
	var props = new Object();
	props.mode = mode;
	props.startPosition = startPosition;
	props.labels = {};
	props.loop = loop;
	props.reversed = reversed;
	cjs.MovieClip.apply(this,[props]);

	// Слой_1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("rgba(0,51,204,0.098)").s().p("AlqB4QiWgxAAhHQAAhGCWgyQCXgxDTAAQDUAACWAxQCXAyAABGQAABHiXAxQiWAyjUAAQjTAAiXgyg");

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-51.3,-17,102.6,34);


// stage content:
(lib._2_HTML5Canvas = function(mode,startPosition,loop,reversed) {
if (loop == null) { loop = true; }
if (reversed == null) { reversed = false; }
	var props = new Object();
	props.mode = mode;
	props.startPosition = startPosition;
	props.labels = {};
	props.loop = loop;
	props.reversed = reversed;
	cjs.MovieClip.apply(this,[props]);

	this.actionFrames = [0];
	// timeline functions:
	this.frame_0 = function() {
		this.start_but.addEventListener("click",f1.bind(this));
		function f1(args){this.play();} 
		
		this.stop_but.addEventListener("click",f2.bind(this));
		function f2(args){this.stop();}
		
		this.reset_but.addEventListener("click",f3.bind(this));
		function f3(args){this.gotoAndStop(1);}
	}

	// actions tween:
	this.timeline.addTween(cjs.Tween.get(this).call(this.frame_0).wait(60));

	// Слой_6
	this.reset_but = new lib.Символ1();
	this.reset_but.name = "reset_but";
	this.reset_but.setTransform(428,448.9,0.1903,0.3037);
	new cjs.ButtonHelper(this.reset_but, 0, 1, 2, false, new lib.Символ1(), 3);

	this.start_but = new lib.Символ1();
	this.start_but.name = "start_but";
	this.start_but.setTransform(327.5,448.9,0.1903,0.3037);
	new cjs.ButtonHelper(this.start_but, 0, 1, 2, false, new lib.Символ1(), 3);

	this.stop_but = new lib.Символ1();
	this.stop_but.name = "stop_but";
	this.stop_but.setTransform(226.1,448.9,0.1902,0.3037);
	new cjs.ButtonHelper(this.stop_but, 0, 1, 2, false, new lib.Символ1(), 3);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.stop_but},{t:this.start_but},{t:this.reset_but}]}).wait(60));

	// Слой_2
	this.instance = new lib.Анимация4("synched",0);
	this.instance.setTransform(183.65,114.15);

	this.timeline.addTween(cjs.Tween.get(this.instance).to({regX:-0.1,regY:-0.1,scaleX:0.9999,scaleY:0.9999,rotation:-178.0245,guide:{path:[183.7,114.3,181.9,115.1,178.9,115.8,175.1,116.8,173.5,117.4,171.8,118.2,169.2,119.8,166,121.9,165,122.4,161.6,124.4,156,126.1,149.6,127.8,146.5,128.8,140.3,130.9,127.9,137.8,116.1,144.3,109.2,146.4,104.2,147.9,93.7,149.4,83.3,150.8,78.2,152.4,73.3,153.9,67.7,156.7,64.2,158.5,57.7,162.3,49.5,167.1,46,170.4,40.5,175.6,35.6,186,27.5,202.8,27.3,203.2,26.5,204.6,24.9,207.3,23.4,209.8,22.6,211.5,19.9,217.2,18.8,227.3,17.9,236,17.7,253.5,17.6,259.9,17.7,262.8,17.9,267.9,18.8,271.9,19.6,275.8,21.9,282.1,24.5,289.5,25.3,292.1,26.5,296.4,27.6,303.7,29,312.6,29.6,315.4,31.9,325.9,36.7,330.9,38.4,332.6,41.7,335,45.5,337.7,46.9,338.9,47.8,339.7,50.9,343.2,53.4,346,55.3,347.2,57.5,348.8,61.6,350.1,67.5,352,68.4,352.3,74.5,354.8,80.5,361.1,81.9,362.5,90.4,372.9,96.4,380.1,102.1,384.7,109.1,390.3,116.5,392.4,120.6,393.6,126,393.9,129.2,394.1,135.7,394.1,183.7,393.7,231.8,393.3,243.2,393.2,248.8,393,258.3,392.6,265.7,391.6,279.8,389.8,294.7,384.8,298.6,383.5,309.7,379.4,312.2,378.4,314.5,377.6]}},29).to({guide:{path:[314.5,377.6,312.2,378.4,309.7,379.4,298.6,383.5,294.7,384.8,279.8,389.8,265.7,391.6,258.3,392.6,248.8,393,243.2,393.2,231.8,393.3,183.7,393.7,135.7,394.1,129.2,394.1,126,393.9,120.6,393.6,116.5,392.4,109.1,390.3,102.1,384.7,96.4,380.1,90.4,372.9,81.9,362.5,80.5,361.1,74.5,354.8,68.4,352.3,67.5,352,61.6,350.1,57.5,348.8,55.3,347.2,53.4,346,50.9,343.2,47.8,339.7,46.9,338.9,45.5,337.7,41.7,335,38.4,332.6,36.7,330.9,31.9,325.9,29.6,315.4,29,312.6,27.6,303.7,26.5,296.4,25.3,292.1,24.5,289.5,21.9,282.1,19.6,275.8,18.8,271.9,17.9,267.9,17.7,262.8,17.6,259.9,17.7,253.5,17.9,236,18.8,227.3,19.9,217.2,22.6,211.5,23.4,209.8,24.9,207.3,26.5,204.6,27.3,203.2,27.5,202.8,35.6,186,40.5,175.6,46,170.4,49.5,167.1,57.7,162.3,64.2,158.5,67.7,156.7,73.3,153.9,78.2,152.4,83.3,150.8,93.7,149.4,104.2,147.9,109.2,146.4,116.1,144.3,127.9,137.8,140.3,130.9,146.5,128.8,149.6,127.8,156,126.1,161.6,124.4,165,122.4,166,121.9,169.2,119.8,171.8,118.2,173.5,117.4,175.1,116.8,178.9,115.8,182.4,115,184.2,114.1,186,113.2,189.6,110.4,192.9,107.7,195,106.8,198.5,105.2,203.5,105.5,205.8,105.7,212.3,106.8,238.6,111.3,273.1,103.8,285.3,101.1,302.7,96,305.3,95.2,308.5,94.3]}},30).wait(1));

	this._renderFirstFrame();

}).prototype = p = new lib.AnMovieClip();
p.nominalBounds = new cjs.Rectangle(286.2,317,185.60000000000002,152.60000000000002);
// library properties:
lib.properties = {
	id: '7FFC16CD12C1824F809AB7C786932A35',
	width: 640,
	height: 480,
	fps: 30,
	color: "#FFFFFF",
	opacity: 1.00,
	manifest: [],
	preloads: []
};



// bootstrap callback support:

(lib.Stage = function(canvas) {
	createjs.Stage.call(this, canvas);
}).prototype = p = new createjs.Stage();

p.setAutoPlay = function(autoPlay) {
	this.tickEnabled = autoPlay;
}
p.play = function() { this.tickEnabled = true; this.getChildAt(0).gotoAndPlay(this.getTimelinePosition()) }
p.stop = function(ms) { if(ms) this.seek(ms); this.tickEnabled = false; }
p.seek = function(ms) { this.tickEnabled = true; this.getChildAt(0).gotoAndStop(lib.properties.fps * ms / 1000); }
p.getDuration = function() { return this.getChildAt(0).totalFrames / lib.properties.fps * 1000; }

p.getTimelinePosition = function() { return this.getChildAt(0).currentFrame / lib.properties.fps * 1000; }

an.bootcompsLoaded = an.bootcompsLoaded || [];
if(!an.bootstrapListeners) {
	an.bootstrapListeners=[];
}

an.bootstrapCallback=function(fnCallback) {
	an.bootstrapListeners.push(fnCallback);
	if(an.bootcompsLoaded.length > 0) {
		for(var i=0; i<an.bootcompsLoaded.length; ++i) {
			fnCallback(an.bootcompsLoaded[i]);
		}
	}
};

an.compositions = an.compositions || {};
an.compositions['7FFC16CD12C1824F809AB7C786932A35'] = {
	getStage: function() { return exportRoot.stage; },
	getLibrary: function() { return lib; },
	getSpriteSheet: function() { return ss; },
	getImages: function() { return img; }
};

an.compositionLoaded = function(id) {
	an.bootcompsLoaded.push(id);
	for(var j=0; j<an.bootstrapListeners.length; j++) {
		an.bootstrapListeners[j](id);
	}
}

an.getComposition = function(id) {
	return an.compositions[id];
}


an.makeResponsive = function(isResp, respDim, isScale, scaleType, domContainers) {		
	var lastW, lastH, lastS=1;		
	window.addEventListener('resize', resizeCanvas);		
	resizeCanvas();		
	function resizeCanvas() {			
		var w = lib.properties.width, h = lib.properties.height;			
		var iw = window.innerWidth, ih=window.innerHeight;			
		var pRatio = window.devicePixelRatio || 1, xRatio=iw/w, yRatio=ih/h, sRatio=1;			
		if(isResp) {                
			if((respDim=='width'&&lastW==iw) || (respDim=='height'&&lastH==ih)) {                    
				sRatio = lastS;                
			}				
			else if(!isScale) {					
				if(iw<w || ih<h)						
					sRatio = Math.min(xRatio, yRatio);				
			}				
			else if(scaleType==1) {					
				sRatio = Math.min(xRatio, yRatio);				
			}				
			else if(scaleType==2) {					
				sRatio = Math.max(xRatio, yRatio);				
			}			
		}
		domContainers[0].width = w * pRatio * sRatio;			
		domContainers[0].height = h * pRatio * sRatio;
		domContainers.forEach(function(container) {				
			container.style.width = w * sRatio + 'px';				
			container.style.height = h * sRatio + 'px';			
		});
		stage.scaleX = pRatio*sRatio;			
		stage.scaleY = pRatio*sRatio;
		lastW = iw; lastH = ih; lastS = sRatio;            
		stage.tickOnUpdate = false;            
		stage.update();            
		stage.tickOnUpdate = true;		
	}
}
an.handleSoundStreamOnTick = function(event) {
	if(!event.paused){
		var stageChild = stage.getChildAt(0);
		if(!stageChild.paused || stageChild.ignorePause){
			stageChild.syncStreamSounds();
		}
	}
}
an.handleFilterCache = function(event) {
	if(!event.paused){
		var target = event.target;
		if(target){
			if(target.filterCacheList){
				for(var index = 0; index < target.filterCacheList.length ; index++){
					var cacheInst = target.filterCacheList[index];
					if((cacheInst.startFrame <= target.currentFrame) && (target.currentFrame <= cacheInst.endFrame)){
						cacheInst.instance.cache(cacheInst.x, cacheInst.y, cacheInst.w, cacheInst.h);
					}
				}
			}
		}
	}
}


})(createjs = createjs||{}, AdobeAn = AdobeAn||{});
var createjs, AdobeAn;