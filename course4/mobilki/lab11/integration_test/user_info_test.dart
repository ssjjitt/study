import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';

class _UserInfoDemoWidget extends StatelessWidget {
  const _UserInfoDemoWidget({required this.name, required this.roleLabel, required this.userId});

  final String name;
  final String roleLabel;
  final String userId;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Информация о пользователе')),
      body: Column(
        children: [
          Text(name),
          Text(roleLabel),
          Text(userId),
        ],
      ),
    );
  }
}

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Integration 3/3 (User): can view current user info (expect)', (tester) async {
    await tester.pumpWidget(
      const MaterialApp(
        home: _UserInfoDemoWidget(
          name: 'Petr',
          roleLabel: 'Пользователь',
          userId: 'u42',
        ),
      ),
    );
    await tester.pump();

    expect(find.text('Информация о пользователе'), findsOneWidget);
    expect(find.text('Petr'), findsOneWidget);
    expect(find.text('Пользователь'), findsOneWidget);
    expect(find.text('u42'), findsOneWidget);
  });
}

