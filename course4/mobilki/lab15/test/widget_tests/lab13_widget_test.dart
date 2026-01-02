import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:hotel_app/add_hotel_page.dart';
import 'package:hotel_app/blocs/auth/auth_bloc.dart';
import 'package:hotel_app/blocs/hotels/hotels_bloc.dart';
import 'package:hotel_app/hotel.dart';
import 'package:hotel_app/main.dart';
import 'package:hotel_app/pages/login_page.dart';
import 'package:hotel_app/pages/register_page.dart';
import 'package:hotel_app/services/auth_service.dart';
import 'package:hotel_app/services/firestore_service.dart';
import 'package:mockito/annotations.dart';
import 'package:mockito/mockito.dart';

import 'lab13_widget_test.mocks.dart';

// ---- network image mock (so HomePage/Image.network won't crash) ----
final _transparentImage = Uint8List.fromList([
  0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4, 0x89, 0x00, 0x00, 0x00,
  0x0A, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9C, 0x63, 0x00, 0x01, 0x00, 0x00,
  0x05, 0x00, 0x01, 0x0D, 0x0A, 0x2D, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x49,
  0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82,
]);

class _MockHttpClient extends Mock implements HttpClient {
  @override
  Future<HttpClientRequest> getUrl(Uri url) async => _MockHttpClientRequest();
}

class _MockHttpClientRequest extends Mock implements HttpClientRequest {
  @override
  Future<HttpClientResponse> close() async => _MockHttpClientResponse();
}

class _MockHttpClientResponse extends Mock implements HttpClientResponse {
  @override
  int get statusCode => 200;

  @override
  int get contentLength => _transparentImage.length;

  @override
  HttpClientResponseCompressionState get compressionState =>
      HttpClientResponseCompressionState.notCompressed;

  @override
  StreamSubscription<List<int>> listen(
    void Function(List<int> event)? onData, {
    Function? onError,
    void Function()? onDone,
    bool? cancelOnError,
  }) {
    return Stream<List<int>>.fromIterable([_transparentImage]).listen(
      onData,
      onError: onError,
      onDone: onDone,
      cancelOnError: cancelOnError,
    );
  }
}

class _TestHttpOverrides extends HttpOverrides {
  @override
  HttpClient createHttpClient(SecurityContext? context) => _MockHttpClient();
}

@GenerateNiceMocks([
  MockSpec<AuthService>(),
  MockSpec<FirestoreService>(),
])
void main() {

  TestWidgetsFlutterBinding.ensureInitialized();

  group('Lab13 Widget Tests — exactly 5 tests (enterText/tap/drag + expect)', () {
    setUpAll(() {
      HttpOverrides.global = _TestHttpOverrides();
    });

    tearDownAll(() {
      HttpOverrides.global = null;
    });

    testWidgets('1) LoginPage: enterText fills Email field (expect)', (tester) async {
      final auth = MockAuthService();

      await tester.pumpWidget(
        BlocProvider<AuthBloc>(
          create: (_) => AuthBloc(auth),
          child: const MaterialApp(home: LoginPage()),
        ),
      );

      await tester.enterText(find.byType(TextFormField).first, 'test@example.com');
      await tester.pump(); // отрисовка

      expect(find.text('test@example.com'), findsOneWidget);
    });

    testWidgets('2) LoginPage: tap \"Забыли пароль?\" navigates (expect)', (tester) async {
      final auth = MockAuthService();

      await tester.pumpWidget(
        BlocProvider<AuthBloc>(
          create: (_) => AuthBloc(auth),
          child: const MaterialApp(home: LoginPage()),
        ),
      );

      await tester.tap(find.text('Забыли пароль?'));
      await tester.pumpAndSettle();

      expect(find.text('Сброс пароля'), findsOneWidget);
    });

    testWidgets('3) RegisterPage: enterText into Name field (expect)', (tester) async {
      final auth = MockAuthService();

      await tester.pumpWidget(
        BlocProvider<AuthBloc>(
          create: (_) => AuthBloc(auth),
          child: const MaterialApp(home: RegisterPage()),
        ),
      );

      await tester.enterText(find.byType(TextFormField).first, 'John');
      await tester.pump();

      expect(find.text('John'), findsOneWidget);
    });

    testWidgets('4) HomePage: drag categories horizontally (expect)', (tester) async {
      final fs = MockFirestoreService();
      when(fs.getHotelsStream()).thenAnswer((_) => Stream<List<Hotel>>.empty());
      when(fs.getHotels()).thenAnswer((_) async => []);

      await tester.pumpWidget(
        BlocProvider<HotelsBloc>(
          create: (_) => HotelsBloc(fs),
          child: const MaterialApp(home: HomePage()),
        ),
      );
      await tester.pump();

      final listViews = find.byType(ListView);
      bool dragged = false;
      for (final el in listViews.evaluate()) {
        final w = el.widget as ListView;
        if (w.scrollDirection == Axis.horizontal) {
          await tester.drag(find.byWidget(w), const Offset(-200, 0));
          await tester.pump();
          dragged = true;
          break;
        }
      }

      expect(dragged, isTrue);
      expect(find.text('Hotel'), findsOneWidget);
    });

    testWidgets('5) AddHotelPage: tap button with empty title shows SnackBar (expect)', (tester) async {
      final fs = MockFirestoreService();
      when(fs.getHotelsStream()).thenAnswer((_) => Stream<List<Hotel>>.empty());
      when(fs.getHotels()).thenAnswer((_) async => []);

      await tester.pumpWidget(
        BlocProvider<HotelsBloc>(
          create: (_) => HotelsBloc(fs),
          child: const MaterialApp(home: AddHotelPage()),
        ),
      );

      await tester.tap(find.text('Добавить отель'));
      await tester.pump();

      expect(find.text('Введите название отеля'), findsOneWidget);
    });
  });
}


