import UIKit
import Flutter

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {

    // имена каналов
    private let BATTERY_CHANNEL = "com.example.platform_demo/battery"
    private let LIGHT_SENSOR_CHANNEL = "com.example.platform_demo/light_sensor"

    override func application(
        _ application: UIApplication,
        didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
    ) -> Bool {
        GeneratedPluginRegistrant.register(with: self)

        guard let controller = window?.rootViewController as? FlutterViewController else {
            return super.application(application, didFinishLaunchingWithOptions: launchOptions)
        }

        // батарея
        let batteryChannel = FlutterMethodChannel(name: BATTERY_CHANNEL, binaryMessenger: controller.binaryMessenger)

        batteryChannel.setMethodCallHandler { [weak self] (call: FlutterMethodCall, result: @escaping FlutterResult) in
            guard call.method == "getBatteryLevel" else {
                result(FlutterMethodNotImplemented)
                return
            }
            self?.receiveBatteryLevel(result: result)
        }

        // датчик освещенности
        // На iOS нет публичного API для прямого доступа к датчику освещённости.
        // просто зарегистрируем обработчик, чтобы Flutter мог получить сообщение об ошибке/недоступности.
        let lightSensorChannel = FlutterEventChannel(name: LIGHT_SENSOR_CHANNEL, binaryMessenger: controller.binaryMessenger)
        lightSensorChannel.setStreamHandler(LightSensorStreamHandler())

        return super.application(application, didFinishLaunchingWithOptions: launchOptions)
    }

    private func receiveBatteryLevel(result: FlutterResult) {
        let device = UIDevice.current
        // вкл мониторинг
        device.isBatteryMonitoringEnabled = true

        if device.batteryState == .unknown {
            result(FlutterError(code: "UNAVAILABLE", message: "Battery info unavailable.", details: nil))
        } else {
            // уровень заряда от 0.1 до 1.0
            result(Int(device.batteryLevel * 100))
        }
    }
}

// датчик
class LightSensorStreamHandler: NSObject, FlutterStreamHandler {
    func onListen(withArguments arguments: Any?, eventSink events: @escaping FlutterEventSink) -> FlutterError? {
        events(FlutterError(code: "UNAVAILABLE", message: "Light sensor API not available on iOS.", details: nil))
        events(FlutterEndOfStream)
        return nil
    }

    func onCancel(withArguments arguments: Any?) -> FlutterError? {
        return nil
    }
}